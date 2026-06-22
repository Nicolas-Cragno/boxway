#include "Rocky.h"

Rocky::Rocky()
{
    cargar("./sprites/Rocky_96");
    fuerza = 8;
    resistencia = 8;
    velocidad = 3;
    setPosicion(100,300);
}
