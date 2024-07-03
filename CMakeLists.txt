cmake_minimum_required(VERSION 3.19)
project(fmod_web)

set(CMAKE_CXX_STANDARD 17)


## copy index to build directory
#####################################################
configure_file(${CMAKE_SOURCE_DIR}/index.html ${CMAKE_BINARY_DIR}/ COPYONLY)

# preload assets
add_link_options("SHELL:--use-preload-plugins"
        "SHELL:--preload-file ${CMAKE_SOURCE_DIR}/assets")

# needs to be set for fmod to work properly in wasm mode
add_link_options("SHELL:-s EXPORTED_RUNTIME_METHODS=['cwrap','setValue','getValue']")
add_link_options("SHELL:-s WASM=1")

add_executable(fmod_web main.cpp)

set(FMOD_DIR "${CMAKE_SOURCE_DIR}/ext/fmod_html5")

# FMod setup
target_include_directories(fmod_web PUBLIC ${FMOD_DIR}/api/core/inc)
target_include_directories(fmod_web PUBLIC ${FMOD_DIR}/api/studio/inc)
target_link_directories(fmod_web PUBLIC ${FMOD_DIR}/api/core/lib/upstream/w32)
target_link_directories(fmod_web PUBLIC ${FMOD_DIR}/api/studio/lib/upstream/w32)

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    
    target_link_libraries(fmod_web ${FMOD_DIR}/api/core/lib/upstream/w32/fmod_wasm.a)
    target_link_libraries(fmod_web ${FMOD_DIR}/api/studio/lib/upstream/w32/fmodstudio_wasm.a)

    target_compile_options(fmod_web PRIVATE "-Wall")
    target_compile_options(fmod_web PRIVATE "-Wextra")
    target_compile_options(fmod_web PRIVATE "-fpermissive")

    target_link_options(fmod_web PRIVATE "SHELL:-s TOTAL_MEMORY=256MB")
    target_link_options(fmod_web PRIVATE "SHELL:-s ALLOW_MEMORY_GROWTH=1")
endif ()
