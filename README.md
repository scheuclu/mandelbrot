# Mandelbrot visualizer
---

Images are combined into a video using this command

```bash
ffmpeg -framerate 30 -pattern_type glob -i 'image_*.pbm' -c:v libx264 -pix_fmt yuv420p out.mp4
  ```
  ---
  
  Click to watch the video.  
  [![IMAGE ALT TEXT](http://img.youtube.com/vi/PzmcI0q1fkQ/0.jpg)](http://www.youtube.com/watch?v=PzmcI0q1fkQ "Video Title")
