#include "Personaje.h"
#include "ImagenPersonaje.h"

Personaje::Personaje()
{
    x = 100;
    y = 100;

    velocidad = 1;
    fuerza = 1;
    resistencia = 1;
    tiempoGolpe= 1 * resistencia / 2;
    duracionGolpe = 1 * fuerza /2;

    vida = 100;

    atacando = false;
    defendiendo = false;

    accionActual = "guardia";
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

    /// ATAQUE / GOLPES

    float auxEntreGolpes;
    auxEntreGolpes = relojGolpes.getElapsedTime().asSeconds();

    if(auxEntreGolpes >= tiempoGolpe)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            accionActual = "jab";

            atacando = true;

            relojGolpes.restart();
            relojAtaque.restart();
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            accionActual = "cross";

            atacando = true;

            relojGolpes.restart();
            relojAtaque.restart();
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            accionActual = "hook";

            atacando = true;

            relojGolpes.restart();
            relojAtaque.restart();
        }
    }

    /// DEFENSA

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        accionActual = "cover";

        defendiendo = true;
    }
}

void Personaje::atacar(Personaje& enemigo)
{
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
