
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "glm/glm.hpp"

struct Mesh
{
public:

private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uv;
    std::vector<int> triangles;
};
