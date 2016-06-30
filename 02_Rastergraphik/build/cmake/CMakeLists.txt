cmake_minimum_required( VERSION 2.6 )

project(exercise2)

# Gebraucht werden OpenGL und GLUT
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Definition der Headerdateien
set(HEADERS
	../../include/tool_base.h
	../../include/application.h
	../../include/bresenham_circle_tool.h
	../../include/bresenham_line_tool.h
	../../include/canvas_renderer.h
	../../include/canvas_buffer.h
	../../include/dda_line_tool.h
	../../include/line_fill_tool.h
	../../include/non_recursive_fill_tool.h
	../../include/pen_tool.h
	../../include/preview_renderer.h
	../../include/rectangle_tool.h
	../../include/recursive_fill_tool.h
	../../include/tiny_vec.h
)



   
# Definition der Sourcedateien
set(SOURCES
	../../src/tool_base.cpp
	../../src/application.cpp
	../../src/bresenham_circle_tool.cpp
	../../src/bresenham_line_tool.cpp
	../../src/canvas_renderer.cpp
	../../src/canvas_buffer.cpp
	../../src/dda_line_tool.cpp
	../../src/line_fill_tool.cpp
	../../src/main.cpp
	../../src/non_recursive_fill_tool.cpp
	../../src/pen_tool.cpp
	../../src/preview_renderer.cpp
	../../src/rectangle_tool.cpp
	../../src/recursive_fill_tool.cpp
)


# Includeverzeichnisse setzen
include_directories(
    ../../include
)


# Support fuer C++-11 aktivieren
set(CMAKE_CXX_FLAGS "-std=c++11")

# Ziel hinzufuegen
add_executable(exercise2
    ${SOURCES}
    ${HEADERS}
)

# Bibliotheken linken
target_link_libraries(exercise2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} -lpthread)
