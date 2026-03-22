# 🎬 ESP32 Cinematic OLED Animation: The End of Vacation

A dramatic, interactive mini-movie built with an ESP32 microcontroller, a 128x64 OLED display, and a buzzer. It humorously captures the profound sadness of a student realizing that the holiday is finally over!

## ✨ Features
* **Multi-Scene Storytelling:** * Scene 1: A side view of a moving bus with engine vibrations.
  * Scene 2: A cinematic camera "pan & zoom" to the student's face.
  * Scene 3: A dramatic close-up showing physical tear drops with dithering shading.
  * Scene 4: A surprise ending sign dropping from above!
* **Interactive Audio:** Uses a passive buzzer to generate synchronized sounds (engine rumble, camera whoosh, water drops, and a heavy thud).
* **Advanced Graphics Engine:** Utilizing `U8g2` library for real-time physics (flowing tears) and carving effects.

## 🛠️ Hardware Requirements
1. **ESP32** Microcontroller.
2. **0.96" OLED Display** (SSD1306 - I2C).
3. **Passive Buzzer**.
4. Jumper wires.

## 🔌 Wiring Diagram
| Component | ESP32 Pin |
| :--- | :--- |
| **OLED SDA** | GPIO 21 |
| **OLED SCL** | GPIO 22 |
| **OLED VCC** | 3.3V |
| **OLED GND** | GND |
| **Buzzer (+)** | GPIO 25 |
| **Buzzer (-)** | GND |

## 🚀 How to Run
1. Clone this repository.
2. Open the `.ino` file in the Arduino IDE.
3. Make sure to install the `U8g2` library by *oliver* from the Library Manager.
4. Compile and upload the code to your ESP32 board.
5. Grab some popcorn and enjoy the sad movie! 🍿😭
