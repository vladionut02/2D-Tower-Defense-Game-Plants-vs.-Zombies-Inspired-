#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    float size,
    glm::vec3 color,
    bool fill) {
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(size * glm::vec3(0, 0, 0), color),
        VertexFormat(size * glm::vec3(-0.5, 4, 0), color),
        VertexFormat(size * glm::vec3(0.5, 4, 0), color),
        VertexFormat(size * glm::vec3(0.5, -4, 0), color),
        VertexFormat(size * glm::vec3(-0.5, -4, 0), color),
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0,1,2, 0,2,3, 0,3,4 ,0,4,1 };

    rectangle->InitFromData(vertices, indices);

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        rectangle->SetDrawMode(GL_TRIANGLES);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateDiamond(
    const std::string& name,
    float size,
    glm::vec3 color,
    bool fill) 
{
   // glm::vec3 diffColor = glm::vec3(0.2, 0.2, 0.2);
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(size * glm::vec3(0, 0, 0), color),
        VertexFormat(size * glm::vec3(-1, 2, 0), color),
        VertexFormat(size * glm::vec3(-1, -2, 0), color),
        VertexFormat(size * glm::vec3(-2, 0, 0), color),
        VertexFormat(size * glm::vec3(-0.8, 0.5, 0), color),
        VertexFormat(size * glm::vec3(1.5, 0.5, 0), color),
        VertexFormat(size * glm::vec3(1.5, -0.5, 0), color),
        VertexFormat(size * glm::vec3(-0.8, -0.5, 0), color),
        
    };

    Mesh* diamond = new Mesh(name);
    std::vector<unsigned int> indices = { 0,1,2, 2,1,3, 6,5,4,6,4,7 };

    diamond->InitFromData(vertices, indices);

    if (!fill) {
        diamond->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        diamond->SetDrawMode(GL_TRIANGLES);
    }

    diamond->InitFromData(vertices, indices);
    return diamond;
}

Mesh* object2D::CreateHexagon(
    const std::string& name,
    float size,
    glm::vec3 color,
    bool fill)
{
    float outerSize = 1.5;
    glm::vec3 innerColor = glm::vec3(0, 0.6, 0.6);

    std::vector<VertexFormat> vertices =
    {
       
        VertexFormat(size * glm::vec3(0, 0, 1), innerColor),
        VertexFormat(size * glm::vec3(1.5, 1.5, 1), innerColor),
        VertexFormat(size * glm::vec3(2.05, -0.55, 1), innerColor),
        VertexFormat(size * glm::vec3(0.55, -2.05, 1), innerColor),
        VertexFormat(size * glm::vec3(-1.5, -1.5, 1), innerColor),
        VertexFormat(size * glm::vec3(-2.05, 0.55, 1), innerColor),
        VertexFormat(size * glm::vec3(-0.55, 2.05, 1), innerColor),

        VertexFormat(outerSize * size * glm::vec3(0, 0, 0), color),
        VertexFormat(outerSize * size * glm::vec3(1.5, 1.5, 0), color),
        VertexFormat(outerSize * size * glm::vec3(2.05, -0.55, 0), color),
        VertexFormat(outerSize * size * glm::vec3(0.55, -2.05, 0), color),
        VertexFormat(outerSize * size * glm::vec3(-1.5, -1.5, 0), color),
        VertexFormat(outerSize * size * glm::vec3(-2.05, 0.55, 0), color),
        VertexFormat(outerSize * size * glm::vec3(-0.55, 2.05, 0), color),

        
        
    };

    std::vector<unsigned int> indices = {
        7,8,9, 7,9,10, 7,10,11, 7,11,12, 7,12,13, 7,13,8,
        0,1,2, 0,2,3, 0,3,4, 0,4,5, 0,5,6, 0,6,1

    };

    Mesh* hexagon = new Mesh(name);

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        hexagon->SetDrawMode(GL_TRIANGLES);
    }

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}


