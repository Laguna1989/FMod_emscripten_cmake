# Running FMod with emscripten and cmake

This repo is a minimal working example of how to run fmod in emscripten(3.1.56) using cmake

# Compilation Steps

Follow the [emscripten getting started](https://emscripten.org/docs/getting_started/downloads.html) steps

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

# Explanations

The ext folder contains a subset of the html5 download from the fmod website 
