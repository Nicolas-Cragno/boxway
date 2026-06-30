---
name: nuevo-personaje
description: Genera los archivos .h y .cpp de un nuevo luchador heredando de Personaje, siguiendo el patron Rocky/Rival
---

El usuario pasara el nombre del nuevo personaje como argumento (ej: /nuevo-personaje Ivan).

Crea dos archivos en el directorio del proyecto:

**NombrePersonaje.h** — siguiendo exactamente el patron de Rocky.h:
```cpp
#pragma once
#include "Personaje.h"

class NombrePersonaje : public Personaje {
public:
    NombrePersonaje();
    void orientacion(bool estado) override;
};
```

**NombrePersonaje.cpp** — siguiendo el patron de Rocky.cpp:
```cpp
#include "NombrePersonaje.h"

NombrePersonaje::NombrePersonaje() {
    imagen.setWidth(205);
    imagen.setHeigth(307);
    imagen.setColumns(5);
    cargar("./sprites/SPRITE_DEL_PERSONAJE.png");
    fuerza = 7;
    resistencia = 6;
    velocidad = 4;
    setPosicion(100, 300);
}

void NombrePersonaje::orientacion(bool estado) {
    if (estado)
        imagen.getSprite().setScale(1.1f, 1.1f);
    else
        imagen.getSprite().setScale(-1.1f, 1.1f);
}
```

Ajusta los stats (fuerza, resistencia, velocidad) para que el personaje tenga un perfil diferente a Rocky (fuerza=8, resistencia=8, velocidad=3).

Despues de crear los archivos, recuerda al usuario:
1. Agregar las dos lineas `<Unit filename="NombrePersonaje.cpp" />` y `<Unit filename="NombrePersonaje.h" />` al archivo BoxWay.cbp
2. Reemplazar `SPRITE_DEL_PERSONAJE.png` con el sprite real
