#pragma once
#include "Personaje.h"
#include "SFML/System.hpp"

class Rival : public Personaje
{
    protected:
        int golpesCombo;
        bool retrocediendo;
        float distanciaRetroceso;
        bool jugadorAtacabaAntes; // estado del jugador en el frame anterior (detecta el INICIO de su golpe)
        bool cubreEsteGolpe; // decision tomada una sola vez por golpe del jugador
        int probCubrirse; // probabilidad (0-100) de bloquear cada golpe
    public:
        /// Cada rival del juego es un Rival con stats distintos, no una clase aparte.
        Rival(float fuerzaRival, float resistenciaRival, float velocidadRival);
        void autoActualizar(Personaje& jugador); // recibe a rocky
        void combinacion();
};
