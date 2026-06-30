#include "Rival.h"
#include <cstdlib>
#include <ctime>

Rival::Rival(float fuerzaRival, float resistenciaRival, float velocidadRival)
{
    setStats(fuerzaRival, resistenciaRival, velocidadRival);

    setPosicion(700,300);

    golpesCombo = 0;

    retrocediendo = false;

    distanciaRetroceso = 0;

    jugadorAtacabaAntes = false;
    cubreEsteGolpe = false;
    probCubrirse = 40; // fijo por ahora; podria variar por rival (Ali cubriria mas que Goyo)
}

void Rival::autoActualizar(Personaje& jugador)
{
    defendiendo = false;

    /// TERMINAR ATAQUE

    if(atacando)
    {
        if(relojAtaque.getElapsedTime().asSeconds() >= duracionGolpe)
        {
            atacando = false;

            accionActual = "guardia";
        }
    }
    else
    {
        accionActual = "guardia";
    }

    /// DISTANCIA CON EL JUGADOR

    float distancia;

    distancia =
    jugador.getPosicion() - getPosicion();

    /// RETROCESO

    if(retrocediendo)
    {
        accionActual = "walk";

        // SI EL JUGADOR ESTA A LA DERECHA
        if(distancia > 0)
        {
            mover(-1,0);

            distanciaRetroceso += velocidad;
        }
        else
        {
            mover(1,0);

            distanciaRetroceso += velocidad;
        }

        // TERMINA RETROCESO
        if(distanciaRetroceso >= 100)
        {
            retrocediendo = false;

            distanciaRetroceso = 0;

            golpesCombo = 0;
        }

        return;
    }

    /// DEFENSA
    /// La decision se toma UNA VEZ por golpe del jugador, en el frame en que lo inicia.
    /// Si tirara rand() en cada frame, la decision cambiaria 60 veces por segundo
    /// y la guardia parpadearia.

    bool jugadorAtacaAhora = jugador.estaAtacando();

    // el golpe RECIEN empieza si ahora ataca y en el frame anterior no
    if(jugadorAtacaAhora && !jugadorAtacabaAntes)
    {
        cubreEsteGolpe = (rand() % 100) < probCubrirse;
    }

    jugadorAtacabaAntes = jugadorAtacaAhora;

    float distanciaAbs = distancia;
    if(distanciaAbs < 0) distanciaAbs = -distanciaAbs; // distancia sin signo

    // se cubre solo si el golpe puede alcanzarlo y no esta a mitad de un golpe propio
    if(jugadorAtacaAhora && cubreEsteGolpe && !atacando && distanciaAbs < 200)
    {
        defendiendo = true;

        accionActual = "cover";

        return; // mientras se cubre no camina ni ataca
    }

    /// ACERCARSE

    if(distancia > 120)
    {
        mover(1,0);

        accionActual = "walk";
    }

    else if(distancia < -120)
    {
        mover(-1,0);

        accionActual = "walk";
    }

    /// ATACAR

    else
    {
        if(
            relojGolpes.getElapsedTime().asSeconds() >= tiempoGolpe
            &&
            !atacando
        )
        {
            atacando = true;
            golpeYaImpacto = false; // golpe nuevo: todavia no le pego a nadie

            combinacion();

            relojGolpes.restart();

            relojAtaque.restart();

            golpesCombo++;

            // DESPUES DE 4 GOLPES
            if(golpesCombo >= 4)
            {
                retrocediendo = true;
            }
        }
    }
}

void Rival::combinacion(){
    int golpe = rand() % 3 + 1;

    switch(golpe){
        case 1:
            accionActual = "jab";
            break;
        case 2:
            accionActual = "cross";
            break;
        case 3:
            accionActual = "hook";
            break;
    }
}
