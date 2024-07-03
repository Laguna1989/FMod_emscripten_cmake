# Running FMod with emscripten and cmake

This repo is a minimal working example of how to run fmod in emscripten using cmake

# Compilation Steps

```bash
mkdir build_web
cd build_web
emcmake cmake ..
emmake make -j

http-server .
```

Open `127.0.0.1:8080` in your browser.

# Known issues

- Firefox complains about wrong mime type (check dev console). This works fine in chrome/chromium 
