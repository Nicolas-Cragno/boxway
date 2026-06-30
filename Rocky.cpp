#include "Rocky.h"

Rocky::Rocky()
{
    imagen.setWidth(205);
    imagen.setHeigth(307);
    imagen.setColumns(5);
    cargar("./sprites/sprites_rocky_2.png");
    fuerza = 8;
    resistencia = 8;
    velocidad = 3;
    setPosicion(100, 300);
}

void Rocky::orientacion(bool estado)
{
    if (estado)
        imagen.getSprite().setScale(1.1f, 1.1f);
    else
        imagen.getSprite().setScale(-1.1f, 1.1f);
}
