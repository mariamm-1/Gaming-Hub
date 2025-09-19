# 🎮 Gaming Hub with TFT Display & LED Matrix

An embedded systems project that integrates **four classic games** with a **Parental Control System**, running on an STM32 microcontroller.  
The project uses both a **TFT display (SPI1 protocol)** and an **8×8 LED Matrix** to provide a fun, interactive, and safe gaming experience.

---

## 📌 Features

- **🕹️ Four Classic Games**
  - 🐍 Snake (LED Matrix)
  - 🦖 Dino Run (TFT)
  - ❌⭕ Tic-Tac-Toe (TFT)
  - 🃏 Memory Match (TFT)

- **👨‍👩‍👧 Parental Control**
  - Configure allowed playtime ⏱️
  - Enable/disable specific games 🎯
  - Child-friendly GUI interface 🖥️

---

## 🖥️ System Architecture

Buttons → GPIO → STM32 MCU → [SPI1 → TFT Display]
→ [GPIO → LED Matrix]
→ [UART → Debugging]


- **MCU:** STM32 (Cortex-M based)  
- **Display 1:** TFT LCD (SPI1 communication)  
- **Display 2:** 8×8 LED Matrix  
- **Inputs:** Push buttons for navigation, selection, and game actions  
- **Debugging:** UART interface  

---

## 🎮 Game Logic Overview

### 🐍 Snake (LED Matrix)
- Snake moves on an 8×8 grid.  
- Food spawns randomly.  
- Grow + score when eating food.  
- Game Over on collision (self or wall).  

### 🦖 Dino Run (TFT)
- Dino jumps over moving obstacles.  
- Jump button → Dino goes up.  
- Scoring based on avoided obstacles.  
- Game Over on collision.  

### ❌⭕ Tic-Tac-Toe (TFT)
- 2-player mode.  
- 3×3 grid with cursor movement + selection.  
- Best-of-3 rounds system with final winner screen.  

### 🃏 Memory Match (TFT)
- 4×4 card grid with 8 pairs.  
- Flip two cards → match or reset.  
- Win if all pairs are found before timer runs out.  
- Lose if timer expires.  

---

## ⚙️ Software Design

- **Language:** C  
- **Framework:** STM32 HAL Drivers  
- **Modules:**  
  - TFT driver (`HTFT_*`)  
  - LED Matrix driver (`HLedMatrix_voidDisplay`)  
  - Game logic headers (`Games_interface.h`)  
- **Randomness:** LFSR (Linear Feedback Shift Register) for Memory Match card shuffle  
- **Debouncing:** Software-based button handling  

---

## 🛠️ Hardware Requirements

- STM32 Development Board  
- TFT LCD Display (SPI1 interface)  
- 8×8 LED Matrix  
- Push Buttons (for input)  
- USB/UART for debugging  

---

## 📷 Screenshots (Examples)

- 🐍 Snake on LED Matrix  
- 🦖 Dino Run on TFT  
- ❌⭕ Tic-Tac-Toe board  
- 🃏 Memory Match cards  

https://drive.google.com/file/d/1mq_a77WTUPJC8G92KHyOLaIjW2jAHQ3D/view?usp=drive_link

---

## 🚀 Future Improvements

- Add sound effects 🎵  
- Wireless parental control (Bluetooth / UART) 📡  
- Additional games 🎲  
- Save high scores to EEPROM 💾  

---

## 👤 Author

👩‍💻 **Mariam**  
📧 Mariam10573@gmail.com
🔗 www.linkedin.com/in/mariam-ashraf-a85371331 

