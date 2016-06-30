cmake_minimum_required( VERSION 2.6 )

project(exercise3)

# Gebraucht werden OpenGL und GLUT
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Definition der Headerdateien
set(HEADERS
	../../include/abstract_scene.h
	../../include/cube_system_split.h
	../../include/example_primitives.h
	../../include/terrain.h
	../../include/application.h
	../../include/example_3d_primitives.h
	../../include/example_trans_order.h
	../../include/tiny_vec.h
	../../include/cube_system.h
	../../include/example_cons_primitives.h
	../../include/recursive_cubes.h
	../../dependencies/qdbmp/include/qdbmp.h
)
   
# Definition der Sourcedateien
set(SOURCES
	../../src/abstract_scene.cpp
	../../src/example_3d_primitives.cpp
	../../src/main.cpp
	../../src/application.cpp
	../../src/example_cons_primitives.cpp
	../../src/recursive_cubes.cpp
	../../src/cube_system.cpp
	../../src/example_primitives.cpp
	../../src/terrain.cpp
	../../src/cube_system_split.cpp
	../../src/example_trans_order.cpp
	../../dependencies/qdbmp/src/qdbmp.cpp
)

# Includeverzeichnisse setzen
include_directories(
    ../../include
	../../dependencies/qdbmp/include
)


# Support fuer C++-11 aktivieren
set(CMAKE_CXX_FLAGS "-std=c++11")

# Ziel hinzufuegen
add_executable(exercise3
    ${SOURCES}
    ${HEADERS}
)

# Bibliotheken linken
target_link_libraries(exercise3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
