cmake_minimum_required(VERSION 2.8)

project(lab10)

add_executable(CubeDraw.out CubeDraw.cpp)
add_executable(CylinderDraw.out CylinderDraw.cpp Cylinder.cpp)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} )


target_link_libraries( CylinderDraw.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} )
target_link_libraries( CubeDraw.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} )

