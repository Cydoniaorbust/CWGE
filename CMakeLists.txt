cmake_minimum_required(VERSION 3.0)
project(CWGE)

add_subdirectory(deps/assimp)
add_subdirectory(deps/glad)
add_subdirectory(deps/glfw)
add_subdirectory(deps/glm)

set(SRC 
	src/Camera.cpp
	src/GLEnvironment.cpp
	src/Model.cpp
	src/Shader.cpp
	src/Texture.cpp )
add_library(CWGE STATIC ${SRC})
# add_library(glad STATIC deps/glad/src/glad.c)

target_link_libraries(CWGE opengl32)
target_link_libraries(CWGE assimp)
target_link_libraries(CWGE glad)
target_link_libraries(CWGE glfw)

target_include_directories(CWGE PUBLIC include/CWGE)
target_include_directories(CWGE PUBLIC deps/assimp/include)
target_include_directories(CWGE PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/deps/glad/include)
target_include_directories(CWGE PUBLIC deps/glfw/deps)
target_include_directories(CWGE PUBLIC deps/glm)
target_include_directories(CWGE PUBLIC deps/stb)