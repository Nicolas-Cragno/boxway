#include "Menu.h"

Menu::Menu(sf::RenderWindow& ventana, sf::Font& fuente)
    : _ventana(ventana), _seleccion(0), _confirmada(-1), _salir(false)
{
    std::vector<std::string> opciones = { "Pelear", "Entrenar", "Estadisticas", "Creditos", "Salir" };

    // Fondo
    _fondo.setSize(sf::Vector2f(1600, 800));
    _fondo.setFillColor(sf::Color(20, 20, 40));

    // Titulo
    _titulo.setFont(fuente);
    _titulo.setString("MENU PRINCIPAL");
    _titulo.setCharacterSize(40);
    _titulo.setFillColor(sf::Color(220, 180, 50));
    _titulo.setStyle(sf::Text::Bold);
    _titulo.setPosition(200, 50);

    // Textos de opciones
    for (int i = 0; i < 5; i++) {
        sf::Text t;
        t.setFont(fuente);
        t.setString(opciones[i]);
        t.setCharacterSize(30);
        t.setPosition(240, 150 + i * 60);
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
        {
            _textos[i].setFillColor(sf::Color(220, 180, 50)); // dorado para opcion elegida
        }
        else
        {
            _textos[i].setFillColor(sf::Color(200, 200, 200)); // gris para no elegidas
        }

    }

    _ventana.draw(_fondo);
    _ventana.draw(_linea);
    _ventana.draw(_titulo);
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
