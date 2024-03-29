# Mandelbrot visualizer
---

## Setup

```bash
sudo apt install g++
sudo apt install imagemagick
mkdir output
```

## Run
```bash
rm output/*; rm main; g++ -fopenmp -O3 main.cpp -o main; ./main
```

## Combine images into a video

```bash
ffmpeg -framerate 30 -pattern_type glob -i 'image_*.png' -c:v libx264 -pix_fmt yuv420p out.mp4
  ```
  ---
  
  **Click to watch the video.**  
  [![IMAGE ALT TEXT](./frame.png)](http://www.youtube.com/watch?v=6KapQf8ZErs)
