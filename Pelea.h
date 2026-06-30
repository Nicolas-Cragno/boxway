#pragma once
#include <SFML/Graphics.hpp>
#include "Rocky.h"
#include "Rival.h"

class Pelea {
public:
    Pelea(sf::RenderWindow& ventana);

    bool cargar();
    void reiniciar(bool entrenamiento);
    void manejarEvento(const sf::Event& evento);
    void actualizar();
    void dibujar();

    bool termino();

private:
    sf::RenderWindow& _ventana;

    Rocky _rocky;
    Rival _rival;

    bool _termino;
    bool _entrenamiento;

    sf::RectangleShape _bgPublico;
    sf::RectangleShape _bgCanvas;
    sf::RectangleShape _bgBorde;
    sf::RectangleShape _bgCuerdas[3];

    sf::Texture _texEntrenamiento;
    sf::Sprite  _spEntrenamiento;
};
