#include "menu.h"
#include "Pelea.h"

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1600, 800), "Rocky Balboa");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return -1;

    Menu menu(window, font);
    Pelea pelea(window);
    if (!pelea.cargar()) return -1;

    bool enMenu = true;  // empieza en el menu

    while (window.isOpen())
    {
        menu.resetOpcionConfirmada();

        sf::Event evento;
        while (window.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                window.close();

            if (enMenu)
                menu.manejarEvento(evento);
            else
                pelea.manejarEvento(evento);
        }

        if (enMenu)
        {
            int op = menu.getSeleccion();
            if (op == 0) enMenu = false;  // Pelear -> entra a la pelea
            if (op == 4) window.close();  // Salir

            window.clear();
            menu.dibujar();
            window.display();
        }
        else
        {
            pelea.actualizar();
            pelea.dibujar();

            if (pelea.termino())
                enMenu = true;  // Escape -> vuelve al menu
        }
    }

    return 0;
}
