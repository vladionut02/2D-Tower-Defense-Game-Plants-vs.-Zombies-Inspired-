#pragma once

#include "components/simple_scene.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#define MOVE_RATIO			(.25f)
#define LIMIT				(.5f)

namespace m1
{


    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void PlaceDiamond(int i, int j, int draggedObj);

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        bool ok;
        bool direction;
        float rotation = 0;
        GLboolean moveRight;
        int collectedStars = 2;
        float collectionTime = 5;
        float spawnTime = 5;
        std::vector<glm::mat3> starMatrices;
        std::vector<std::pair<glm::mat3, int>> hexagonMatrices;
        int nrOfLives = 3;
        int randNum = (rand() * 1.0 / RAND_MAX * 3);
        int randColor;
        glm::ivec2 mousePosition;
        bool drag = false;
        int dragedObj = -1;
    };
}   // namespace m1
