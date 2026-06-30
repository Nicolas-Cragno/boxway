#include "Pelea.h"

Pelea::Pelea(sf::RenderWindow& ventana)
    // Rival no tiene constructor vacio, hay que darle los stats aca.
    // El orden de la lista sigue el orden de declaracion en Pelea.h.
    : _ventana(ventana), _rival(6, 6, 2), // Goyo Peralta: fuerza, resistencia, velocidad
      _termino(false), _entrenamiento(false)
{
    _bgPublico.setSize(sf::Vector2f(1600, 560));
    _bgPublico.setFillColor(sf::Color(25, 20, 45));

    _bgCanvas.setSize(sf::Vector2f(1600, 240));
    _bgCanvas.setPosition(0, 560);
    _bgCanvas.setFillColor(sf::Color(205, 170, 110));

    _bgBorde.setSize(sf::Vector2f(1600, 14));
    _bgBorde.setPosition(0, 550);
    _bgBorde.setFillColor(sf::Color(80, 55, 30));

    for (int i = 0; i < 3; i++) {
        _bgCuerdas[i].setSize(sf::Vector2f(1600, 7));
        _bgCuerdas[i].setPosition(0, 310 + i * 70);
        _bgCuerdas[i].setFillColor(sf::Color(190, 40, 40));
    }
}

bool Pelea::cargar()
{
    if (!_rival.cargar("./sprites/rocky_96.png")) return false;

    if (_texEntrenamiento.loadFromFile("./backgrounds/fondo_entrenamiento.png")) {
        sf::Vector2u sz = _texEntrenamiento.getSize();
        _spEntrenamiento.setTexture(_texEntrenamiento);
        _spEntrenamiento.setScale(1600.f / sz.x, 800.f / sz.y);
    }

    _rocky.orientacion(true);
    _rival.orientacion(false);

    return true;
}

void Pelea::reiniciar(bool entrenamiento)
{
    _entrenamiento = entrenamiento;
    _termino = false;
    _rocky.reiniciar(200, 462);
    _rival.reiniciar(1300, 462);
    _rocky.orientacion(true);
    _rival.orientacion(false);
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

    if (!_entrenamiento)
        _rival.autoActualizar(_rocky);

    // Rocky golpea al rival (hitbox y no sprite completo: el sprite tiene mucho aire transparente)
    if (_rocky.estaAtacando())
    {
        if (_rocky.getHitbox().intersects(_rival.getHitbox()))
        {
            _rocky.atacar(_rival);
        }
    }

    // Rival golpea a Rocky (solo en pelea, no en entrenamiento)
    if (!_entrenamiento && _rival.estaAtacando())
    {
        if (_rival.getHitbox().intersects(_rocky.getHitbox()))
        {
            _rival.atacar(_rocky);
        }
    }

    // En entrenamiento no hay ganador: se sale solo con Escape.
    // Sin este !_entrenamiento, matar al muñeco cortaba el entrenamiento a los pocos golpes.
    if (!_entrenamiento && (_rocky.getVida() <= 0 || _rival.getVida() <= 0))
        _termino = true;
}

void Pelea::dibujar()
{
    _ventana.clear();
    if (_entrenamiento) {
        _ventana.draw(_spEntrenamiento);
    } else {
        _ventana.draw(_bgPublico);
        _ventana.draw(_bgCanvas);
        _ventana.draw(_bgBorde);
        for (int i = 0; i < 3; i++)
            _ventana.draw(_bgCuerdas[i]);
    }
    _rocky.dibujar(_ventana);
    _rival.dibujar(_ventana);
    _ventana.display();
}

bool Pelea::termino()
{
    return _termino;
}
