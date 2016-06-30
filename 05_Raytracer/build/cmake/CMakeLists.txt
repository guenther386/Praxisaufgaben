cmake_minimum_required( VERSION 2.6 )

project(exercise5)


# Definition der Headerdateien
set(HEADERS
	../../include/blinn_phong.h        
	../../include/kd_tree.h
	../../include/point_light.h      
	../../include/spot_light.h
	../../include/box.h                
	../../include/light_source.h  
	../../include/primitive_group.h  
	../../include/timing.h
	../../include/camera.h             
	../../include/material.h      
	../../include/primitive.h        
	../../include/tiny_vec.h
	../../include/cylinder.h           
	../../include/mat.h           
	../../include/ray.h              
	../../include/transformation_group.h
	../../include/directional_light.h  
	../../include/obj_reader.h    
	../../include/raytracer.h        
	../../include/triangle.h
	../../include/image_io.h           
	../../include/phong.h         
	../../include/scene.h            
	../../include/utils.h
	../../include/intersection_info.h  
	../../include/plane.h         
	../../include/sphere.h           
	../../include/vec.h
)
   
# Definition der Sourcedateien
set(SOURCES
	../../src/blinn_phong.cpp        
	../../src/light_source.cpp  
	../../src/primitive_group.cpp
	../../src/box.cpp                
	../../src/main.cpp          
	../../src/raytracer.cpp
	../../src/camera.cpp             
	../../src/material.cpp      
	../../src/scene.cpp
	../../src/cylinder.cpp           
	../../src/phong.cpp         
	../../src/sphere.cpp
	../../src/directional_light.cpp  
	../../src/plane.cpp         
	../../src/spot_light.cpp
	../../src/intersection_info.cpp  
	../../src/point_light.cpp   
	../../src/transformation_group.cpp
	../../src/kd_tree.cpp            
	../../src/primitive.cpp     
	../../src/triangle.cpp
)

# Includeverzeichnisse setzen
include_directories(
    ../../include
)


# Support fuer C++-11 aktivieren
set(CMAKE_CXX_FLAGS "-std=c++11")

# Ziel hinzufuegen
add_executable(exercise5
    ${SOURCES}
    ${HEADERS}
)

# Bibliotheken linken
target_link_libraries(exercise5)
