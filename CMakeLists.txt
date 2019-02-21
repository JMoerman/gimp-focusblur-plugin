cmake_minimum_required(VERSION 3.0)
project(FocusBlur C)

set (PLUGIN_DIR "/usr/lib/gimp/2.0/plug-ins/" CACHE STRING "Directory in which the plugin should be installed.")
option (USE_MP "Build with multithreading support." TRUE)
option (USE_FFTW3 "Use the FFTW3 library." TRUE)
option (NO_COMPLEX_BUILTIN "Do not use complex.h" FALSE)

find_package (PkgConfig)

if (USE_MP)
    add_definitions(-DENABLE_MP)
endif ()

if (USE_FFTW3)
    pkg_check_modules (FFTW3 REQUIRED
        fftw3f
        fftw3
    )
    set (FFT_SOURCES
        src/fftblurbuffer.c
        src/fftblur.c
    )
    add_definitions(-DHAVE_FFTW3)
    add_definitions(${FFTW3_CFLAGS})
    link_directories(${FFTW3_LIBRARY_DIRS})
endif ()

pkg_check_modules (DEPS REQUIRED
    gegl-0.4
    gtk+-2.0>=2.24
    gimp-2.0
    gimpui-2.0
)

add_definitions(${DEPS_CFLAGS})
link_directories(${DEPS_LIBRARY_DIRS})

find_file (COMPLEX_H_PATH complex.h)
if (COMPLEX_H_PATH AND NOT NO_COMPLEX_BUILTIN)
    add_definitions(-DHAVE_COMPLEX_H)
endif ()

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/libgimp)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(gimp-plugin-focusblur
    src/aaa.c
    src/diffusion.c
    src/fftblurproc.c
    src/focusblurrc.c
    src/interface.c
    src/source.c
    src/brush.c
    src/focusblurenums.c
    src/focusblurstock.c
    src/render.c
    src/depthmap.c
    src/focusblurparam.c
    src/gimpplugin.c
    src/shine.c
    ${FFT_SOURCES}
)
target_link_libraries(gimp-plugin-focusblur
  m
  ${DEPS_LIBRARIES}
  ${FFTW3_LIBRARIES}
)

install (TARGETS gimp-plugin-focusblur DESTINATION ${PLUGIN_DIR})
