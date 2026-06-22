#include "Rival.h"
#include <cstdlib>
#include <ctime>

Rival::Rival()
{
    setPosicion(700,300);

    golpesCombo = 0;

    retrocediendo = false;

    distanciaRetroceso = 0;
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
