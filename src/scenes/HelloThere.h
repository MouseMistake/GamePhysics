#pragma once

#include "core/Simple2DScene.h"
#include <glm/gtc/matrix_transform.hpp>

/*

Code by Niels Van Son (BA6) as Assignment 1 for the Game Physics class.

Note: The class name was just created that way when originally taught how to create a new one.
It's still Assignment 1.

Disclosure:
Code is my own. No AI tools were used.

*/

class HelloThere : public Simple2DScene {
public:
    HelloThere();
    ~HelloThere();

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;
    void DrawCube(glm::vec2 centerPoint, float circleRadius);

    virtual const char* GetName() override { return "Assignment 1"; };

private:
    glm::vec2 defaultCirclePosition = glm::vec2(0, 5);
    glm::vec2 circle1Velocity = glm::vec2(0, 0);
    glm::vec2 circle2Velocity = glm::vec2(0, 0);
    glm::vec2 circle3Velocity = glm::vec2(0, 0);

    glm::vec2 circle1Position;
    glm::vec2 circle2Position;
    glm::vec2 circle3Position;
    float circle1Radius;
    float circle2Radius;
    float circle3Radius;

    float gravity = -9.81f;
    float maxFallingSpeed = 10.0f;

    // Collision stuff
    glm::vec2 collision1Normal;
    glm::vec2 collision2Normal;
    glm::vec2 collision3Normal;

    float intersection1Depth;
    float intersection2Depth;
    float intersection3Depth;

    // Encapsulating rectangle corners
    glm::vec2 bottomLeft = glm::vec2(-5, 0);
    glm::vec2 bottomRight = glm::vec2(5, 0);

    glm::vec2 topLeft = glm::vec2(-5, 6);
    glm::vec2 topRight = glm::vec2(5, 6);

};
