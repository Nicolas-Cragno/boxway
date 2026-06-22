#pragma once
#include "Personaje.h"
#include "SFML/System.hpp"

class Rival : public Personaje
{
    protected:
        int golpesCombo;
        bool retrocediendo;
        float distanciaRetroceso;
    public:
        Rival();
        void autoActualizar(Personaje& jugador); // recibe a rocky
        void combinacion();
};
