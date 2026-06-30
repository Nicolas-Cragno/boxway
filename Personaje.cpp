#include "Personaje.h"
#include "ImagenPersonaje.h"

Personaje::Personaje()
{
    x = 100;
    y = 100;

    setStats(1, 1, 1); // stats base; cada personaje los pisa en su propio constructor

    vida = 100;

    atacando = false;
    defendiendo = false;
    golpeYaImpacto = false;

    accionActual = "guardia";
}

void Personaje::setStats(float nuevaFuerza, float nuevaResistencia, float nuevaVelocidad)
{
    /// Ningun stat puede bajar de 1: resistencia y velocidad se usan como divisores.
    if(nuevaFuerza < 1) nuevaFuerza = 1;
    if(nuevaResistencia < 1) nuevaResistencia = 1;
    if(nuevaVelocidad < 1) nuevaVelocidad = 1;

    fuerza = nuevaFuerza;
    resistencia = nuevaResistencia;
    velocidad = nuevaVelocidad;

    recalcularDerivados();
}

void Personaje::recalcularDerivados()
{
    /// Cadencia de golpes: cuanto mas veloz el personaje, mas seguido golpea.
    /// 1.5 es el tiempo base en segundos. Rocky (velocidad 3) queda en 0.5 seg.
    tiempoGolpe = 1.5f / velocidad;

    /// El golpe ocupa el 60% del ciclo. Tiene que ser MENOR que tiempoGolpe:
    /// si no, el golpe anterior nunca terminaria antes de habilitarse el siguiente.
    duracionGolpe = tiempoGolpe * 0.6f;
}

bool Personaje::cargar(std::string archivo)
{
    return imagen.setTextura(archivo); // devuelve true si funciona
}

void Personaje::mover(float dx, float dy)
{
    x += dx * velocidad;
    y += dy * velocidad;

    imagen.getSprite().setPosition(x,y);
}

void Personaje::setPosicion(float px, float py)
{
    x = px;
    y = py;

    imagen.getSprite().setPosition(x, y);
}

void Personaje::actualizar()
{
    defendiendo = false;

    if(atacando){
        if(relojAtaque.getElapsedTime().asSeconds() >= duracionGolpe)
        {
            atacando = false;
            accionActual = "guardia";
        }

    } else {
        accionActual = "guardia";
    }

    /// MOVIMIENTO

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        mover(1,0);

        accionActual = "walk";
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        mover(-1,0);

        accionActual = "walk";
    }

    /// DEFENSA
    /// Se evalua ANTES que los golpes: cubrirse y pegar son excluyentes.
    /// !atacando evita cubrirse a mitad de un golpe (bloquear mientras el puño viaja).

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !atacando)
    {
        accionActual = "cover";

        defendiendo = true;
    }

    /// ATAQUE / GOLPES

    float auxEntreGolpes;
    auxEntreGolpes = relojGolpes.getElapsedTime().asSeconds();

    if(auxEntreGolpes >= tiempoGolpe && !defendiendo)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            accionActual = "jab";

            atacando = true;
            golpeYaImpacto = false; // golpe nuevo: todavia no le pego a nadie

            relojGolpes.restart();
            relojAtaque.restart();
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            accionActual = "cross";

            atacando = true;
            golpeYaImpacto = false;

            relojGolpes.restart();
            relojAtaque.restart();
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            accionActual = "hook";

            atacando = true;
            golpeYaImpacto = false;

            relojGolpes.restart();
            relojAtaque.restart();
        }
    }
}

void Personaje::atacar(Personaje& enemigo)
{
    /// Pelea::actualizar() llama a esta funcion en CADA frame mientras el golpe
    /// este en curso. Sin esta guarda un solo golpe descontaria vida unas 30 veces
    /// (60 FPS x duracionGolpe). La bandera se reinicia al empezar el proximo golpe.
    if(golpeYaImpacto) return;

    golpeYaImpacto = true;

    if(!enemigo.estaDefendiendo())
    {
        enemigo.recibirDanio(5 * fuerza); // 5 (puede ser cualquier nro) multiplicado por la fuerza del personaje
    } else {
        enemigo.recibirDanio(1); // recibe un danio muy menor (lo va cansando);
    }
}

void Personaje::recibirDanio(float danio)
{
    if(danio < 0) danio = 0;

    vida -= (danio/ resistencia); // danio que manda el enemigo dividido por la resistencia del personaje

    if(vida < 0) vida = 0;
}

void Personaje::dibujar(sf::RenderWindow& ventana)
{
    imagen.dibujar(ventana, accionActual);
}

void Personaje::orientacion(bool estado)
{
    if(estado){
        imagen.getSprite().setScale(3.5f,3.5f);
    } else {
        imagen.getSprite().setScale(-3.5f,3.5f);
    }
}

float Personaje::getVida()
{
    return vida;
}

void Personaje::reiniciar(float px, float py)
{
    vida = 100;
    atacando = false;
    defendiendo = false;
    golpeYaImpacto = false;
    accionActual = "guardia";
    setPosicion(px, py);
}

float Personaje::getX()
{
    return x;
}

float Personaje::getY()
{
    return y;
}

float Personaje::getPosicion()
{
    return
        getSprite().getGlobalBounds().left
        +
        getSprite().getGlobalBounds().width / 2;
}

bool Personaje::estaAtacando()
{
    return atacando;
}
bool Personaje::estaDefendiendo()
{
    return defendiendo;
}

sf::Sprite& Personaje::getSprite()
{
    return imagen.getSprite();
}

sf::FloatRect Personaje::getHitbox()
{
    /// La caja del sprite incluye el aire transparente alrededor del cuerpo
    /// (la del rival escalado mide 336x336). Para que un golpe conecte a
    /// distancia de piña y no de un metro, achicamos la caja: nos quedamos
    /// con el 40% central del ancho y el 80% central del alto.
    sf::FloatRect caja = getSprite().getGlobalBounds();

    float margenX = caja.width * 0.30f;  // 30% de recorte por costado
    float margenY = caja.height * 0.10f; // 10% arriba y abajo

    return sf::FloatRect(
        caja.left + margenX,
        caja.top + margenY,
        caja.width - 2 * margenX,
        caja.height - 2 * margenY
    );
}
