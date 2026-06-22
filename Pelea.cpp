#include "Pelea.h"

Pelea::Pelea(sf::RenderWindow& ventana)
    : _ventana(ventana), _termino(false)
{
    // Rocky se carga solo en su constructor (cargar + posicion + stats)
    // Rival solo tiene posicion en su constructor, falta sprite y orientacion
}

bool Pelea::cargar()
{
    // Rocky ya esta listo desde su constructor

    // Rival necesita cargar el sprite y orientacion



    _rival.orientacion(false);   // escala negativa = mira a la izquierda

    return true;
}

void Pelea::manejarEvento(const sf::Event& evento)
{
    if (evento.type == sf::Event::KeyPressed)
        if (evento.key.code == sf::Keyboard::Escape)
            _termino = true;
}

void Pelea::actualizar()
{
    _rocky.actualizar();
    _rival.autoActualizar(_rocky);

    // Rocky golpea al rival
    if (_rocky.estaAtacando())
    {
        if (_rocky.getSprite().getGlobalBounds().intersects(
                _rival.getSprite().getGlobalBounds()))
        {
            _rocky.atacar(_rival);
        }
    }

    // Rival golpea a Rocky
    if (_rival.estaAtacando())
    {
        if (_rival.getSprite().getGlobalBounds().intersects(
                _rocky.getSprite().getGlobalBounds()))
        {
            _rival.atacar(_rocky);
        }
    }
}

void Pelea::dibujar()
{
    _ventana.clear();
    _rocky.dibujar(_ventana);
    _rival.dibujar(_ventana);
    _ventana.display();
}

bool Pelea::termino()
{
    return _termino;
}
