#pragma once

#include <functional>
#include <chrono>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#ifdef _DEBUG
#include <glad/glad.h>
#else
#include <glad/glad.h>
#endif

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>