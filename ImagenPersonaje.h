#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class ImagenPersonaje {
    private:
        sf::Sprite sprite;
        sf::Texture textura;
        int frame_width = 96; // alto
        int frame_heigth = 96; // ancho
        int frame_actual[2] = {};
        int spritesPorFila = 5;
        float velocidadRender = 1; // tiempo de cambio entre render y render

    public:
        ImagenPersonaje();
        // setters
        bool setTextura(const std::string& archivo); // imagen completa
        void setSprite(int fila = 0, int columna = 0); // sprite especifico
        void setWidth(int);
        void setHeigth(int);
        void setColumns(int);
        void setVelocidad(int);
        // getters
        void dibujar(sf::RenderWindow& ventana, std::string accion);
        sf::Sprite& getSprite();
        // animacion
        int frameAnimacion = 0;
        sf::Clock relojAnimacion;
        float tiempoAnimacion = 2;
};
