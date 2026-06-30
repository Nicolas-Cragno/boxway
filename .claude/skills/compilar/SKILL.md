---
name: compilar
description: Compila BoxWay con g++ usando SFML local y reporta errores de compilacion
disable-model-invocation: true
---

Ejecuta el siguiente comando desde el directorio del proyecto BoxWay para compilar:

```powershell
cd "C:\Users\RonaldNoguera\OneDrive - Alephee\Escritorio\Claude\boxway"
g++ -g -Wall -fexceptions -I"./SFML/include" main.cpp ImagenPersonaje.cpp Personaje.cpp Rocky.cpp Rival.cpp Menu.cpp Pelea.cpp -o "bin/Debug/BoxWay.exe" -L"./SFML/lib" -lsfml-graphics-d -lsfml-window-d -lsfml-system-d 2>&1
```

- Si hay errores, muestralos completos con numero de linea y archivo.
- Si compila sin errores, responde: "Compilacion exitosa. Ejecutable en bin/Debug/BoxWay.exe"
- Si hay warnings pero no errores, muestra los warnings y confirma que compilo.
