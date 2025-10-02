# Juego Tres en Raya

Un clásico Tres en Raya para consola, desarrollado en C++, con soporte de colores en la terminal para diferenciar a los jugadores.

Ideal para aprender conceptos básicos de programación en C++, manejo de clases y colores en consola.

---

## Instalación

### 1. Clona o descarga este repositorio

```bash
git clone https://github.com/Santiagox01/estructura_2025
```

### 2. Abre la carpeta en tu IDE/compilador C++ favorito

- Dev-C++
- Code::Blocks
- Visual Studio Code

### 3. Compila los archivos principales

```bash
cd Juego
clang++ -std=c++11 -o TresEnRaya JuegoTresEnRaya.cpp Player.cpp
```

**Archivos necesarios:**
- `JuegoTresEnRaya.cpp`
- `Player.cpp`
- `Player.h`
- `Color.h`

>  **Nota:** Asegúrate de que tu compilador soporte C++11 o superior.

---

##  Uso

1. **Ejecuta el programa compilado**
   ```bash
   ./TresEnRaya
   ```

2. **El juego es para dos jugadores:**
   - Jugador 1 (X) comienza siempre
   - Jugador 2 (O) juega después

3. **Cada jugador elige una casilla (del 1 al 9) según la siguiente disposición:**

   ```
   1 | 2 | 3
   ---------
   4 | 5 | 6
   ---------
   7 | 8 | 9
   ```

4. **Gana quien logre alinear tres símbolos** (horizontal, vertical o diagonal)

5. **Si el tablero se llena y nadie gana**, el resultado es empate

6. **Al finalizar**, podrás elegir jugar otra ronda o salir del juego

---

##  Colores en Terminal

🟥 **Jugador 1 (X):** Rojo  
🟦 **Jugador 2 (O):** Azul

Esto facilita la identificación de los turnos durante la partida.

---

##  Contribuciones



Si deseas mejorar el proyecto, contacta a:

- [@Santiagox01](https://github.com/Santiagox01)
- [@YForondaa](https://github.com/YForondaa)
- [@jaiderehaco-eng](https://github.com/jaiderehaco-eng)

---

##  Desarrollado por

**Estudiantes del ITM:**

- Santiago Jaramillo Valencia
- Yenifer Foronda Hernández
- Jayder Alejandro Arias Arango

---

**¡Disfruta del juego!** 
