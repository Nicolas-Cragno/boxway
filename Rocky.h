#pragma once
#include "Personaje.h"

class Rocky : public Personaje
{
    public:
    Rocky();
    void orientacion(bool estado) override;
};
