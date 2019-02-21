cmake_minimum_required(VERSION 3.0)
project(FocusBlur)

find_package (PkgConfig)

pkg_check_modules (DEPS REQUIRED
    gegl-0.4
    gtk+-2.0>=2.24
    fftw3f
    fftw3
    gimp-2.0
    gimpui-2.0
)
add_definitions(${DEPS_CFLAGS})
add_definitions(-DHAVE_FFTW3 -DENABLE_MP)
link_directories(${DEPS_LIBRARY_DIRS})
include_directories(${LIBGIMP_INCLUDE_DIR})

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
    src/fftblurbuffer.c
    src/focusblurenums.c
    src/focusblurstock.c
    src/render.c
    src/depthmap.c
    src/fftblur.c
    src/focusblurparam.c
    src/gimpplugin.c
    src/shine.c)
target_link_libraries(gimp-plugin-focusblur
  m
  ${DEPS_LIBRARIES})

