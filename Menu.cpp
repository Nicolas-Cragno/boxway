#include "Menu.h"

Menu::Menu(sf::RenderWindow& ventana, sf::Font& fuente)
    : _ventana(ventana), _seleccion(0), _confirmada(-1), _salir(false)
{
    std::vector<std::string> opciones = { "Pelear", "Entrenar", "Estadisticas", "Creditos", "Salir" };

    if (_texFondo.loadFromFile("./backgrounds/fondo_menu.png")) {
        sf::Vector2u sz = _texFondo.getSize();
        _spFondo.setTexture(_texFondo);
        _spFondo.setScale(1600.f / sz.x, 800.f / sz.y);
    }
    _fondo.setSize(sf::Vector2f(1600, 800));
    _fondo.setFillColor(sf::Color(0, 0, 0, 60));

    _titulo.setFont(fuente);
    _titulo.setString("BOXWAY");
    _titulo.setCharacterSize(80);
    _titulo.setFillColor(sf::Color(220, 180, 50));
    _titulo.setStyle(sf::Text::Bold);
    sf::FloatRect tb = _titulo.getLocalBounds();
    _titulo.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    _titulo.setPosition(800.f, 160.f);

    _linea.setSize(sf::Vector2f(420.f, 3.f));
    _linea.setFillColor(sf::Color(220, 180, 50, 160));
    _linea.setOrigin(210.f, 1.5f);
    _linea.setPosition(800.f, 230.f);

    _resaltado.setFillColor(sf::Color(220, 180, 50, 35));
    _resaltado.setOutlineColor(sf::Color(220, 180, 50, 100));
    _resaltado.setOutlineThickness(1.f);

    for (int i = 0; i < 5; i++) {
        sf::Text t;
        t.setFont(fuente);
        t.setString(opciones[i]);
        t.setCharacterSize(34);
        sf::FloatRect r = t.getLocalBounds();
        t.setOrigin(r.left + r.width / 2.f, r.top + r.height / 2.f);
        t.setPosition(800.f, 310.f + i * 72.f);
        _textos.push_back(t);
    }
}

void Menu::manejarEvento(const sf::Event& evento)
{
    if (evento.type != sf::Event::KeyPressed) return; // sin esto avanza x2

    if (evento.key.code == sf::Keyboard::Up) _seleccion = (_seleccion - 1 + 5) % 5;

    if (evento.key.code == sf::Keyboard::Down) _seleccion = (_seleccion + 1) % 5;

    if (evento.key.code == sf::Keyboard::Return) _confirmada = _seleccion;

    if (_confirmada == 4) _salir = true;
}

void Menu::dibujar()
{
    for (int i = 0; i < 5; i++) {
        if (i == _seleccion)
            _textos[i].setFillColor(sf::Color(220, 180, 50));
        else
            _textos[i].setFillColor(sf::Color(180, 180, 180));
    }

    sf::FloatRect r = _textos[_seleccion].getGlobalBounds();
    _resaltado.setSize(sf::Vector2f(r.width + 60.f, 52.f));
    _resaltado.setOrigin(_resaltado.getSize().x / 2.f, _resaltado.getSize().y / 2.f);
    _resaltado.setPosition(_textos[_seleccion].getPosition());

    _ventana.draw(_spFondo);
    _ventana.draw(_fondo);
    _ventana.draw(_linea);
    _ventana.draw(_titulo);
    _ventana.draw(_resaltado);
    for (int i = 0; i < 5; i++)
        _ventana.draw(_textos[i]);
}

int Menu::getSeleccion()
{
    return _confirmada;
}

bool Menu::quiereSalir()
{
    return _salir;
}

void Menu::resetOpcionConfirmada(){
    _confirmada = -1;
}
