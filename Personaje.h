#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "ImagenPersonaje.h"

class Personaje {
    protected:
        ImagenPersonaje imagen;
        float resistencia;
        float fuerza;
        float velocidad;
        float tiempoGolpe; // cada cuanto golpea
        float duracionGolpe; // cuanto dura el golpe/contacto
        float x;
        float y;
        float posicionReal; // para calcular colisiones
        float vida;
        bool atacando;
        bool defendiendo;
        sf::Clock relojGolpes;
        sf::Clock relojAtaque; // principalmente para el tiempo donde se muestra el frame de golpe

        std::string accionActual;

    public:
        Personaje();
        bool cargar(std::string archivo);
        void mover(float dx, float dy); // "direccion" x / y
        void setPosicion(float px, float py); // "posicion" x / y
        void setAccion(std::string accion);
        void actualizar();
        void atacar(Personaje& enemigo);
        void recibirDanio(float danio);
        float getVida();
        void reiniciar(float px, float py);
        float getX(); // para automatizacion del rival
        float getY(); // para automatizacion del rival
        float getPosicion();
        bool estaAtacando();
        bool estaDefendiendo();
        void dibujar(sf::RenderWindow& ventana);
        virtual void orientacion(bool); // positiva se posiciona a la izq y negativo a la derecha
        sf::Sprite& getSprite();
};
