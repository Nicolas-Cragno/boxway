#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
    private:
        sf::RenderWindow& _ventana;
        int _seleccion;
        int _confirmada;
        bool _salir;
        sf::Texture _texFondo;
        sf::Sprite  _spFondo;
        sf::RectangleShape _fondo;
        sf::RectangleShape _linea;
        sf::RectangleShape _resaltado;
        sf::Text _titulo;
        std::vector<sf::Text> _textos;

    public:
        Menu(sf::RenderWindow& ventana, sf::Font& fuente);
        void manejarEvento(const sf::Event& evento);
        void dibujar();
        int getSeleccion();
        bool quiereSalir();
        void resetOpcionConfirmada();
};
