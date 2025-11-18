#needs at least CMake 3.10 to build (safe modern baseline)
cmake_minimum_required(VERSION 3.10)

#sets name of project
project (Raytracer)

#Use the C++ 17 standard
set(CMAKE_CXX_STANDARD 17)

#Force compiler to actually use C++ 17
set(CMAKE_CXX_STANDARD_REQUIRED True)

#build an executable 'Raytracer.exe' from the following files, later add more like vec3.cpp
add_executable(Raytracer 
    src/main.cpp)




# --- Saved for Eckart Young in future --- #   
#add_executable(Eckart_Young 
    #src/Eckart_Young.cpp)

#Look in /include for headers
#target_include_directories(Eckart_Young PRIVATE ${CMAKE_SOURCE_DIR}/include)
#target_include_directories(Raytracer PRIVATE ${CMAKE_SOURCE_DIR}/include)