#pragma once

#include <functional>
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#ifdef _DEBUG
#include "Glad/GladDeb/glad.h"
#else
#include "Glad/GladRel/glad.h"
#endif

#include "Glfw/include/GLFW/glfw3.h"

#include "Glm/glm.hpp"
#include "Glm/gtc/matrix_transform.hpp"
#include "Glm/gtc/type_ptr.hpp"

#include "Assimp/Importer.hpp"
#include "Assimp/scene.h"
#include "Assimp/postprocess.h"