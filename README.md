# 🎇 Interactive Rotating Spirals (OpenGL + GLUT)

This is a fun and interactive C program using OpenGL and GLUT to render **rotating spiral patterns** . Users can interact using the **keyboard and mouse** to change spiral types, count, colors, and more.

---

## 📸 Features

- Multiple spiral patterns:
  - Archimedean Spiral
  - Flower Spiral
  - Pulsating Spiral
  - Star Spiral
  - Rose Curve
- Rotation and dynamic scaling of spirals
- Color randomization
- Interactive controls using keyboard and mouse
- Real-time animation using GLUT timer

---

## 🛠️ Requirements

- OpenGL Utility Toolkit (GLUT)
- GCC or any compatible C compiler

---

## 🔧 Run Instructions

# Compile the program
gcc main.c -o screensaver.exe -I"C:\MinGW\include" -L"C:\MinGW\lib" -lfreeglut -lopengl32 -lglu32

# Run the program
./screensaver


## 🎮 Controls

| Key / Mouse        | Action                                |
|--------------------|----------------------------------------|
| `+`                | Increase spiral count                  |
| `-`                | Decrease spiral count                  |
| `S` or `s`         | Switch to the next spiral type         |
| `C` or `c`         | Randomize colors for all spirals       |
| `R` or `r`         | Reset spiral configuration             |
| `ESC`              | Exit the program                       |
| Left Mouse Click   | Reverse spiral rotation direction      |
| Right Mouse Click  | Change spiral colors randomly          |
