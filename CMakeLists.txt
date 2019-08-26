cmake_minimum_required(VERSION 3.0)
project(CWGE)

# add_subdirectory(deps/assimp)
# add_subdirectory(deps/glad)
# add_subdirectory(deps/glfw)
# add_subdirectory(deps/glm)

set(SRC 
	src/Camera.cpp
	src/GLEnvironment.cpp
	src/Model.cpp
	src/Shader.cpp
	src/Texture.cpp )
add_library(CWGE STATIC ${SRC})
add_library(glad STATIC deps/unused/glad/src/glad.c)
find_library(GLFW_LIB glfw3 deps/unused/glfw/lib-vc2017)
find_library(ASSIMP_LIB assimp deps/unused/assimp)

target_link_libraries(CWGE opengl32)
target_link_libraries(CWGE ${ASSIMP_LIB})
target_link_libraries(CWGE glad)
target_link_libraries(CWGE ${GLFW_LIB})

target_include_directories(CWGE PUBLIC include/CWGE)
# target_include_directories(CWGE PUBLIC deps/assimp/include)
target_include_directories(CWGE PUBLIC deps/unused/assimp/include)

# target_include_directories(CWGE PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/deps/glad/include)
# target_include_directories(CWGE PUBLIC deps/glfw/deps)
target_include_directories(glad PUBLIC deps/unused/glad/include)
target_include_directories(CWGE PUBLIC deps/unused/glad/include)
target_include_directories(CWGE PUBLIC deps/unused/glfw/include)

target_include_directories(CWGE PUBLIC deps/glm)
target_include_directories(CWGE PUBLIC deps/stb)