#include "ImagenPersonaje.h"

ImagenPersonaje::ImagenPersonaje(){
    // constructor
}

bool ImagenPersonaje::setTextura(const std::string& archivo) // imagen completa
{
    if(!textura.loadFromFile(archivo)){
        return false;
    }
textura.setSmooth(false);
    sprite.setTexture(textura);


    return true;
}

void ImagenPersonaje::setSprite(int fila, int columna)
{
    frame_actual[0] = fila;
    frame_actual[1] = columna;

    sprite.setTextureRect(
        sf::IntRect(
            columna * frame_width,
            fila * frame_heigth,
            frame_width,
            frame_heigth
        )
    );
}

void ImagenPersonaje::setWidth(int ancho)
{
    frame_width = ancho;
}

void ImagenPersonaje::setHeigth(int alto)
{
    frame_heigth = alto;
}

void ImagenPersonaje::setColumns(int columnas)
{
    spritesPorFila = columnas;
}

void ImagenPersonaje::setVelocidad(int velocidad)
{
    velocidadRender = velocidad;
}

void ImagenPersonaje::dibujar(sf::RenderWindow& ventana, std::string accion)
{
    if(accion == "walk"){

    if(relojAnimacion.getElapsedTime().asSeconds() >= 0.2f){

        if(frameAnimacion == 2){
            frameAnimacion = 0;
        }
        else{
            frameAnimacion++;
        }

        relojAnimacion.restart();
    }

    setSprite(0, frameAnimacion);
}
    else if(accion == "jab"){
            setSprite(1,0);
    }
    else if(accion == "cross") {
        setSprite(1,1);
    }
    else if(accion == "hook"){
        setSprite(1,3);
    }
    else if(accion == "cover") {
        setSprite(1,4);
    }
    else{
        setSprite(0,0);
    }

    ventana.draw(sprite);
}

sf::Sprite& ImagenPersonaje::getSprite()
{
    return sprite;
}
