# Juego Tres en Raya

Un clásico Tres en Raya para consola, desarrollado en C++, con soporte de colores en la terminal para diferenciar a los jugadores.

Ideal para aprender conceptos básicos de programación en C++, manejo de clases y colores en consola.

---

## Instalación

### 1. Clona o descarga este repositorio

```bash
git clone https://github.com/Santiagox01/estructura_2025
```

### 2. Compila el juego

```bash
make
```

>  **Nota:** Asegúrate de que tu compilador soporte C++11 o superior.

---

##  Uso

1. **Ejecuta el programa compilado**
   ```bash
   make run
   ```
   o directamente:
   ```bash
   ./TresEnRaya
   ```

2. **Menú Principal:**
   - **Nueva Partida**: Inicia una nueva sesión de juego
   - **Cargar Partida Guardada**: Continúa una partida previamente guardada
   - **Gestionar Partidas Guardadas**: Ver y eliminar partidas guardadas
   - **Instrucciones**: Ver cómo jugar
   - **Salir**: Cerrar el juego

3. **Nueva Partida:**
   - Ingresa un nombre para tu partida
   - Elige quién comienza (Jugador 1, Jugador 2 o aleatorio)
   - Juega múltiples rondas consecutivas
   - Después de cada partida verás las puntuaciones actuales
   - Puedes continuar jugando o salir

4. **Cada jugador elige una casilla (del 1 al 9) según la siguiente disposición:**

   ```
   1 | 2 | 3
   ---------
   4 | 5 | 6
   ---------
   7 | 8 | 9
   ```

5. **Guardar Partida:**
   - Durante el juego, escribe `guardar` en tu turno para guardar y salir
   - Al terminar una serie de partidas, se te preguntará si deseas guardar

6. **Gana quien logre alinear tres símbolos** (horizontal, vertical o diagonal)

7. **Si el tablero se llena y nadie gana**, el resultado es empate

---

##  Características

🎮 **Modo de Partidas Continuas**: Juega múltiples rondas bajo el mismo nombre de partida  
📊 **Puntuaciones Automáticas**: Ve los resultados acumulados después de cada partida  
💾 **Sistema de Guardado**: Guarda tu progreso en cualquier momento  
🎨 **Símbolos con Colores**: X en Rojo, O en Azul para fácil identificación en el tablero  
🎲 **Inicio Aleatorio**: Opción de seleccionar aleatoriamente quién comienza

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
