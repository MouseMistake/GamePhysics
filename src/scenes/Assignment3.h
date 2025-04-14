#pragma once

#include "core/Simple2DScene.h"
#include <vector>
#include <string>

/*

Code by Niels Van Son (BA6) as Assignment 3 for the Game Physics class.

Disclosure:
Deepseek was used to cross-reference and digest physics concepts as well as discuss potential implementations.
It was used for research purposes and the code is my own. No copy-paste was used.

*/

class Assignment3 : public Simple2DScene {
public:
    Assignment3();
    ~Assignment3();

    struct Circle {
        glm::vec2 pos;
        float radius;
        float mass;
        glm::vec2 vel;
        glm::vec2 force;

    };

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment 3"; };

private:
    void ReadMouseInput();

    glm::vec2 impulse;

    bool isMouseDown;
    int8_t selectedCircle;

    std::vector<Circle> circles;
    std::vector<glm::vec2> circlePathPositions;

    glm::vec2 gravity = glm::vec2(0, -9.81f);

    glm::vec2 baseDragPosition;
};
