#pragma once

#include "core/Simple2DScene.h"
#include <string>

/*

Code by Niels Van Son (BA6) as Assignment 2 for the Game Physics class.

Disclosure:
Code is my own. GPT was briefly used to fix an issue with the forcefield's dimensions (inverted min and max for AABB def.)
The force field is the AABB rectangle.

*/

class Assignment2 : public Simple2DScene {
public:
    Assignment2();
    ~Assignment2();

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;
    void AddForce(glm::vec2 forceAmount);
    void AddForcePush(glm::vec2 forceAmount);

    virtual const char* GetName() override { return "Assignment 2"; };

    void Reset();

private:
    float circleRadius;
    glm::vec2 circlePosition;
    glm::vec2 circlePositionDefault = glm::vec2(0, 5);
    float circleMass;

    glm::vec2 circleVelocity;
    glm::vec2 circleAcceleration;
    
    glm::vec2 gravity = glm::vec2(0, 9.81f);
    float maxSpeed = 15.0f;
    float fallingSpeed = 0.0f;

    glm::vec2 totalAppliedForce;

    // Encapsulating rectangle corners
    glm::vec2 bottomLeft = glm::vec2(-5, 0);
    glm::vec2 bottomRight = glm::vec2(5, 0);

    glm::vec2 forceFieldForce = glm::vec2(0.0f, 15.0f);
    glm::vec2 forceFieldMin = glm::vec2(-10, -10);
    glm::vec2 forceFieldMax = glm::vec2(10, 10);

};
