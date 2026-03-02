#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;

namespace transform2D {
    glm::vec2 ExtractTranslation(const glm::mat3& matrix) {
        return glm::vec2(matrix[2][0], matrix[2][1]);
    }

    glm::vec2 ExtractScale(const glm::mat3& matrix) {
        float scaleX = glm::length(glm::vec2(matrix[0][0], matrix[0][1]));
        float scaleY = glm::length(glm::vec2(matrix[1][0], matrix[1][1]));
        return glm::vec2(scaleX, scaleY);
    }
}
/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void Tema1::PlaceDiamond(int i, int j, int draggedObj)
{
    // Check if the position is valid
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(180 + i * 160, 100 + j * 150);
    switch (dragedObj)
    {
    case 0:
        std::cout << "release" << std::endl;
        RenderMesh2D(meshes["redDiamond"], shaders["VertexColor"], modelMatrix);
        break;
    case 1:
        RenderMesh2D(meshes["blueDiamond"], shaders["VertexColor"], modelMatrix);
        break;
    case 2:
        RenderMesh2D(meshes["lightBlueDiamond"], shaders["VertexColor"], modelMatrix);
        break;
    case 3:
        RenderMesh2D(meshes["whiteDiamond"], shaders["VertexColor"], modelMatrix);
        break;
    }
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 50;
  

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

   

    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0 ), true);
    AddMeshToList(square1);

    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0.45f, 0.45f, 0.45f), false);
    AddMeshToList(square3);

    Mesh* redDiamond = object2D::CreateDiamond("redDiamond", 20,  glm::vec3(1, 0, 0), true);
    AddMeshToList(redDiamond);

    Mesh* blueDiamond = object2D::CreateDiamond("blueDiamond", 20, glm::vec3(0, 0, 1), true);
    AddMeshToList(blueDiamond);

    Mesh* lightBlueDiamond = object2D::CreateDiamond("lightBlueDiamond", 20, glm::vec3(0.459f, 0.647f, 1), true);
    AddMeshToList(lightBlueDiamond);

    Mesh* whiteDiamond = object2D::CreateDiamond("whiteDiamond", 20, glm::vec3(1, 1, 1), true);
    AddMeshToList(whiteDiamond);

    Mesh* mesh = new Mesh("star");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "meshes"), "star.obj");
    meshes[mesh->GetMeshID()] = mesh;

    Mesh* whiteHexagon = object2D::CreateHexagon("whiteHexagon", 10, glm::vec3(1, 1, 1), true);
    AddMeshToList(whiteHexagon);

    Mesh* blueHexagon = object2D::CreateHexagon("blueHexagon", 10, glm::vec3(0, 0, 1), true);
    AddMeshToList(blueHexagon);

    Mesh* redHexagon = object2D::CreateHexagon("redHexagon", 10, glm::vec3(1, 0, 0), true);
    AddMeshToList(redHexagon);

    Mesh* lightBlueHexagon = object2D::CreateHexagon("lightBlueHexagon", 10, glm::vec3(0.459f, 0.647f, 1), true);
    AddMeshToList(lightBlueHexagon);

    Mesh* rectangle = object2D::CreateRectangle("rectangle", 50, glm::vec3(1, 0, 0), true);
    AddMeshToList(rectangle);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    collectionTime -= deltaTimeSeconds;

    if (collectionTime <= 0) {
        collectionTime = rand() % 10 + 4;
        randNum = (rand() * 1.0 / RAND_MAX * 3) + 1;
        for (int i = 0; i < randNum; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(rand() % resolution.x, rand() % resolution.y);
            modelMatrix *= transform2D::Scale(6.0f, 6.0f);
            starMatrices.push_back(modelMatrix);
        }
    }
    for (const auto& starMatrix : starMatrices) {
        RenderMesh2D(meshes["star"], starMatrix, glm::vec3(0.8, 0, 1));
    }
    
    translateX += 200 * deltaTimeSeconds;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1700, 75);
    modelMatrix *= transform2D::Translate(-translateX, translateY);
    RenderMesh2D(meshes["redHexagon"], shaders["VertexColor"], modelMatrix);
    spawnTime -= deltaTimeSeconds;
    if (spawnTime <= 0) {
        translateX += 100 * deltaTimeSeconds;
        spawnTime = rand() % 10 + 3;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(resolution.x, 75 + rand() % 3 * 150);
        randColor = rand() % 4;
        hexagonMatrices.push_back(std::make_pair(modelMatrix, randColor));
    }

    for (const auto& hexagon : hexagonMatrices) {
        const auto& hexagonMatrix = hexagon.first;
        randColor = hexagon.second;
        switch (randColor)
        {
        case 1:
            RenderMesh2D(meshes["redHexagon"], shaders["VertexColor"], hexagonMatrix);
            break;
        case 2:
            RenderMesh2D(meshes["whiteHexagon"], shaders["VertexColor"], hexagonMatrix);
            break;
        case 3:
            RenderMesh2D(meshes["blueHexagon"], shaders["VertexColor"], hexagonMatrix);
            break;
        default:
            RenderMesh2D(meshes["lightBlueHexagon"], shaders["VertexColor"], hexagonMatrix);
            break;
        }
        
    }

    if (drag && dragedObj != -1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(mousePosition.x, 720 - mousePosition.y);
        switch (dragedObj) {
        case 0:
            if (collectedStars > 0) {
                RenderMesh2D(meshes["redDiamond"], shaders["VertexColor"], modelMatrix);
                break;
            }
        case 1:
            if (collectedStars > 1) {
                RenderMesh2D(meshes["blueDiamond"], shaders["VertexColor"], modelMatrix);
                break;
            }
        case 2:
            if (collectedStars > 1) {
                RenderMesh2D(meshes["lightBlueDiamond"], shaders["VertexColor"], modelMatrix);
                break;
            }
        case 3:
            if (collectedStars > 2) {
                RenderMesh2D(meshes["whiteDiamond"], shaders["VertexColor"], modelMatrix);
                break;
            }
        }
    }

    
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(200, 450);
    rotation -= deltaTimeSeconds;
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(3 * rotation);
    modelMatrix *= transform2D::Scale(5.0f, 5.0f);
    RenderMesh2D(meshes["star"], modelMatrix, glm::vec3(1, 0, 0));


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(50, 225);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
   
    for (int i = 0; i < 3; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(820 + 105 * i, 650);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(100 + i * 130, 25 + j * 150);
            modelMatrix *= transform2D::Scale(2.0f, 2.0f);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        }
    }

    for (int i = 0; i < 4; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(50 + i * 190, 600);
        modelMatrix *= transform2D::Scale(2.0f, 2.0f);
        RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100 + 3 * 190, 650);
    RenderMesh2D(meshes["whiteDiamond"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100 + 2 * 190, 650);
    RenderMesh2D(meshes["lightBlueDiamond"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100 + 1 * 190, 650);
    RenderMesh2D(meshes["blueDiamond"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100 + 0 * 190, 650);
    RenderMesh2D(meshes["redDiamond"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(140 + 3 * 190, 575);
    modelMatrix *= transform2D::Scale(5.0f, 5.0f);
    RenderMesh2D(meshes["star"], modelMatrix, glm::vec3(0.8, 0.8, 0.8));
    
    for (int i = 1; i < 4; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(95 + i * 190, 575);
        modelMatrix *= transform2D::Scale(5.0f, 5.0f);
        RenderMesh2D(meshes["star"], modelMatrix, glm::vec3(0.8, 0.8, 0.8));
    }

    for (int i = 0; i < 4; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(50 + i * 190, 575);
        modelMatrix *= transform2D::Scale(5.0f, 5.0f);
        RenderMesh2D(meshes["star"], modelMatrix, glm::vec3(0.8, 0.8, 0.8));
    }
    int aux = 0;
    int newLine = 0;
    int counter = 0;
    for (int i = 0; i < collectedStars; i++) { 
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(795 + aux, 620 - newLine);
        modelMatrix *= transform2D::Scale(5.0f, 5.0f);
        RenderMesh2D(meshes["star"], modelMatrix, glm::vec3(0.8, 0.8, 0.8));
        counter++;
        aux += 45;
        if (counter == 10) {
            aux = 0;
            newLine += 45;
            counter = 0;
        }   
    }
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    mousePosition.x = mouseX;
    mousePosition.y = mouseY;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == 1) {
        int x_scena_joc = mouseX;
        int y_scena_joc = 720 - mouseY;
        auto clickedStar = starMatrices.end(); // Initialize to end to check if any star is clicked

        for (auto it = starMatrices.begin(); it != starMatrices.end(); ++it) {
            glm::vec2 starPosition = transform2D::ExtractTranslation(*it);
            glm::vec2 starScale = transform2D::ExtractScale(*it);

            // Calculate AABB boundaries
            float left = starPosition.x - starScale.x * 4;
            float right = starPosition.x + starScale.x * 4;
            float bottom = starPosition.y - starScale.y * 3.5;
            float top = starPosition.y + starScale.y * 4;

            // Check if the mouse is within the AABB
            if (x_scena_joc >= left && x_scena_joc <= right &&
                y_scena_joc >= bottom && y_scena_joc <= top) {
                // Mouse is inside the AABB of the star, it's clicked!
                clickedStar = it;
                break;
            }
        }

        // Check if a star was clicked
        if (clickedStar != starMatrices.end()) {
            // Remove the clicked star from the vector
            starMatrices.erase(clickedStar);
            collectedStars++;
        }

        for (int i = 0; i < 4; i++) {
            // Calculate the bounds of the square

            float squareCenterX = 100 + i * 190;
            float squareCenterY = 650;
            float squareSize = 50;
            float leftLim = squareCenterX - squareSize;
            float rightLim = squareCenterX + squareSize;
            float topLim = squareCenterY + squareSize;
            float botLim = squareCenterY - squareSize;

            // Check if the mouse is within the bounds of the current square
            if (x_scena_joc >= leftLim && x_scena_joc <= rightLim &&
                y_scena_joc >= botLim && y_scena_joc <= topLim) {
                drag = true;
                dragedObj = i;

                break; // Break the loop once a square is clicked
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    int sceneX = mouseX;
    int sceneY = 720 - mouseY;


    if (drag && dragedObj != -1) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                float squareCenterX = 180 + i * 160;
                float squareCenterY = 100 + j * 150;
                float squareSize = 50;
                float leftLim = squareCenterX - squareSize;
                float rightLim = squareCenterX + squareSize;
                float topLim = squareCenterY + squareSize;
                float botLim = squareCenterY - squareSize;

                // Check if the mouse is within the bounds of the current square
                if (sceneX >= leftLim && sceneX <= rightLim &&
                    sceneY >= botLim && sceneY <= topLim) {
                    PlaceDiamond(i, j, dragedObj);
                    
                    break; // Break the loop once a square is clicked
                }
            }
        }

    }

    drag = false;
    dragedObj = -1;
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
