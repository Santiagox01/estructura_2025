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

## Arquitectura del Proyecto

### Clases Principales

#### **MenuController**
- **Responsabilidad**: Gestiona el menú principal y la navegación del juego
- **Métodos principales**:
  - `showMainMenu()`: Muestra el menú principal con 5 opciones
  - `showInstructions()`: Muestra las instrucciones del juego
  - `handleNewGame()`: Inicia una nueva partida
  - `handleLoadGame()`: Carga una partida guardada
  - `run()`: Ejecuta el loop principal del menú

#### **GameSession**
- **Responsabilidad**: Maneja la lógica de las sesiones de juego (nuevas o cargadas)
- **Métodos principales**:
  - `playNew()`: Ejecuta una nueva partida con loop continuo de rondas
  - `playFromSaved()`: Reanuda una partida guardada
  - `chooseStartingPlayer()`: Permite elegir quién comienza
  - `handleGameEnd()`: Procesa el resultado de una partida (victoria o empate)

#### **Board**
- **Responsabilidad**: Gestiona el estado del tablero y la lógica del juego
- **Métodos principales**:
  - `makeMove()`: Registra un movimiento en el tablero
  - `isValidMove()`: Valida si un movimiento es legal
  - `checkWin()`: Verifica si hay un ganador
  - `isFull()`: Comprueba si el tablero está lleno
  - `print()`: Muestra el tablero con símbolos coloreados
  - `getState()` / `setState()`: Gestiona el estado para guardar/cargar

#### **Player**
- **Responsabilidad**: Representa a un jugador y maneja su entrada
- **Atributos**:
  - `symbol`: El símbolo del jugador (X u O)
  - `name`: Nombre del jugador (Jugador 1 o Jugador 2)
- **Métodos**:
  - `makeMove()`: Solicita y valida la entrada del jugador

#### **ScoreManager**
- **Responsabilidad**: Gestiona las puntuaciones y su persistencia
- **Métodos principales**:
  - `incrementPlayer1Wins()`: Incrementa victorias del Jugador 1
  - `incrementPlayer2Wins()`: Incrementa victorias del Jugador 2
  - `incrementDraws()`: Incrementa contador de empates
  - `display()`: Muestra la tabla de puntuaciones
  - `save()` / `load()`: Guarda y carga puntuaciones desde `scores.txt`

#### **SaveGameManager**
- **Responsabilidad**: Gestiona el guardado y carga de partidas
- **Métodos principales**:
  - `save()`: Guarda una nueva partida
  - `update()`: Actualiza una partida existente o crea una nueva
  - `load()`: Carga una partida por índice
  - `list()`: Lista todas las partidas guardadas
  - `deleteGame()`: Elimina una partida guardada
  - `manage()`: Interfaz para gestionar partidas guardadas

#### **Color** (Clase de utilidad)
- **Responsabilidad**: Proporciona funciones para colorear texto en terminal
- **Métodos estáticos**:
  - `rojo()`: Retorna texto en color rojo (para X)
  - `azul()`: Retorna texto en color azul (para O)
  - `reset()`: Resetea el color del terminal

### Estructuras de Datos

#### **GameState**
- Almacena el estado completo de una partida:
  - `board`: Vector con el estado del tablero
  - `currentPlayer`: Símbolo del jugador actual
  - `p1Symbol` / `p2Symbol`: Símbolos asignados a cada jugador
  - `player1Symbol`: Símbolo original del Jugador 1
  - `name`: Nombre de la partida

#### **Score**
- Almacena las puntuaciones:
  - `player1Wins`: Victorias del Jugador 1
  - `player2Wins`: Victorias del Jugador 2
  - `draws`: Cantidad de empates

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
