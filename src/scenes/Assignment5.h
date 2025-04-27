#pragma once

#include "core/Simple2DScene.h"
#include <vector>
#include <string>
#include <iostream>

/*

Code by Niels Van Son (BA6) as Assignment 5 for the Game Physics class.

Disclaimer:
ChatGPT was briefly used to discuss the wall normals and making sure the ball
reflects correctly everywhere. Code is my own.

I did not necessarily follow the slides's code (especially regarding drag)
because I wanted to try my own thing.

*/

class Assignment5 : public Simple2DScene {
public:
    Assignment5();
    ~Assignment5();

    // I'm baking the projected dot product distance value in the struct this time
    struct Circle {
        glm::vec2 pos;
        float radius;
        float mass;
        glm::vec2 vel;
        glm::vec2 force;
        float projectedDistance;
        int8_t id;
        bool hasDropped;

    };

    struct Hole {
        glm::vec2 pos;
        float radius;
        int8_t id;
    };

    // Just so we can access it more easily later
    struct Wall {
        glm::vec2 startPoint;
        glm::vec2 endPoint;
        glm::vec2 lineNormal;

    };

    virtual void OnEnable() override;
    virtual void OnDisable() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void DrawGUI() override;

    virtual const char* GetName() override { return "Assignment 5"; };

private:
    void ReadMouseInput();
    void UpdateCueBall(float dt);
    void TestWallCollision(Circle& ball);
    void AssignBallPositions();

    glm::vec2 GetLineNormal(glm::vec2 lineStart, glm::vec2 lineEnd);

    glm::vec2 impulse = glm::vec2(0);

    bool isMouseDown;
    int8_t selectedCircle;

    float ballRadius = 0.9f;
    float ballMass = 1.0f;

    uint8_t howManyDropped;
    bool signalNewDropped = false;

    std::vector<Circle> poolBalls;
    std::vector<Hole> poolHoles;
    std::vector<Wall> poolWalls;

    // The white ball thing, that's called the cue ball apparently
    Circle cueBall = {};

    glm::vec2 baseDragPosition = glm::vec2(0);
};
