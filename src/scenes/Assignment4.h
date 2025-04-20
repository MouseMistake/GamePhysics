#pragma once

#include "core/Simple2DScene.h"

/*

Code by Niels Van Son (BA6) as Assignment 4 for the Game Physics class.

Disclosure:
Deepseek was used to cross-reference C++ syntax and physics definitions.
Code is my own. No copy-paste was used.

*/

class Assignment4 : public Simple2DScene {
public:
    Assignment4();
    ~Assignment4();

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

    glm::vec2 GetLineNormal(glm::vec2 lineStart, glm::vec2 lineEnd);

    virtual const char* GetName() override { return "Assignment 4"; };

private:
    glm::vec2 groundStart = glm::vec2(-5, -2);
    glm::vec2 groundEnd = glm::vec2(5, 2);

    glm::vec2 lineNormal = glm::vec2(0);

    glm::vec2 gravity = glm::vec2(0, -9.81f);

    Circle mainCircle;

    float projectedDistance = 0;

};
