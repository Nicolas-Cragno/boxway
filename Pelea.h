#pragma once
#include <SFML/Graphics.hpp>
#include "Rocky.h"
#include "Rival.h"

class Pelea {
public:
    Pelea(sf::RenderWindow& ventana);

    bool cargar();
    void manejarEvento(const sf::Event& evento);
    void actualizar();
    void dibujar();

    bool termino();

private:
    sf::RenderWindow& _ventana;

    Rocky _rocky;
    Rival _rival;

    bool _termino;
};
