#include "Rocky.h"

Rocky::Rocky()
{
    imagen.setWidth(205);
    imagen.setHeigth(307);
    imagen.setColumns(5);
    cargar("./sprites/sprites_rocky_2.png");
    setStats(8, 8, 3); // fuerza, resistencia, velocidad
    setPosicion(100, 300);
}

void Rocky::orientacion(bool estado)
{
    if (estado)
        imagen.getSprite().setScale(1.1f, 1.1f);
    else
        imagen.getSprite().setScale(-1.1f, 1.1f);
}
