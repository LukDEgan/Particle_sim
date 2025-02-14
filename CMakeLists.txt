cmake_minimum_required(VERSION 3.26.0)
project(Particle_Sim VERSION 1.0.0)

find_package(OpenGL REQUIRED)

link_directories(dependencies/lib)

add_executable(Particle_Sim 
    src/main.c 
    src/glad.c)

target_include_directories(Particle_Sim PRIVATE dependencies/include)

target_link_libraries(Particle_Sim glfw OpenGL::GL)