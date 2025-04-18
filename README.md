# Implementing Image Filters using OpenMP

This C++ project demonstrates the use of **OpenMP** to accelerate image processing tasks such as blurring, converting to grayscale, and adding a bluish tint. The project uses **OpenCV** for image operations and provides a simple console interface for users to choose filters and apply them to any input image.

---

## 🛠️ Features

- 📸 **Blur Filter** — Applies a Gaussian-like blur using parallel computation.
- 🖤 **Grayscale Filter** — Converts the image into grayscale using weighted RGB channels.
- 💙 **Bluish Tint Filter** — Enhances the blue channel to give a bluish tone.
- ⚡ **OpenMP Acceleration** — Filters are applied using parallel for-loops to boost performance.

---

## 🖼️ Screenshots

### 📋 Program Interface
| Screenshot | Description |
|------------|-------------|
| ![Step 1](./filters/11.png) | Input image prompt |
| ![Step 2](./filters/12.png) | Blur the Image |
| ![Step 2](./filters/14.png) | Convert to Grayscale |
| ![Step 3](./filters/13.png) | Add Bluish Tint |

### 🧪 Filter Outputs

| Filter Output | Description |
|---------------|-------------|
| ![Output 1](./filters/blurredme.jpg) | Blurred image |
| ![Output 2](./filters/bluishme.jpg) | Bluish tint applied |
| ![Output 3](./filters/grayishme.jpg) | Grayscale image |

---

## 🚀 How to Run

1. Make sure **OpenCV** and **OpenMP** are installed and properly linked.
2. Compile the code using a compiler that supports OpenMP:
   ```bash
   g++ -fopenmp -o image_filters filters.cpp `pkg-config --cflags --libs opencv4`
