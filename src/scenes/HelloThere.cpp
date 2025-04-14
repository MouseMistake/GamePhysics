#include "HelloThere.h"

#include "imgui.h"
#include "../core/PhysicsUtils.h"
#include <iostream>

HelloThere::HelloThere()
    : circle1Position(
          glm::vec2(defaultCirclePosition.x + 3, defaultCirclePosition.y)),
      circle2Position(
          glm::vec2(defaultCirclePosition.x, defaultCirclePosition.y)),
      circle3Position(
          glm::vec2(defaultCirclePosition.x - 3, defaultCirclePosition.y)),
      circle1Radius(0.75f),
      circle2Radius(0.75f),
      circle3Radius(0.75f) {}

HelloThere::~HelloThere(){};

void HelloThere::OnEnable() {}

void HelloThere::OnDisable() {}

void HelloThere::Update(float deltaTime) {
    // Adding gravity
    circle1Velocity.y += gravity * deltaTime;
    circle2Velocity.y += gravity * deltaTime;
    circle3Velocity.y += gravity * deltaTime;

    circle1Position.y += circle1Velocity.y * deltaTime;
    circle2Position.y += circle2Velocity.y * deltaTime;
    circle3Position.y += circle3Velocity.y * deltaTime;

    float falling1Speed = glm::length(circle1Velocity);
    if (falling1Speed > maxFallingSpeed) {
        circle1Velocity = glm::normalize(circle1Velocity) * maxFallingSpeed;

    }

    float falling2Speed = glm::length(circle2Velocity);
    if (falling2Speed > maxFallingSpeed) {
        circle2Velocity = glm::normalize(circle2Velocity) * maxFallingSpeed;

    }

    float falling3Speed = glm::length(circle3Velocity);
    if (falling3Speed > maxFallingSpeed) {
        circle3Velocity = glm::normalize(circle3Velocity) * maxFallingSpeed;

    }

    // Simpler intergration
    if (circle1Position.y < circle1Radius) {
        circle1Velocity.y += 3;
        
    }
    if (circle2Position.y < circle2Radius) {
        circle2Velocity.y += 5;
        
    }
    if (circle3Position.y < circle3Radius) {
        circle3Velocity.y += 7;
        
    }

    // PhysicsUtils implementation (Too complicated for what we're doing here):
    /*
    if (PhysicsUtils::IsCollidingRectRect(
        circle1Position, 0.0f, glm::vec2(0.5f),
        glm::vec2(0, 0), 0.0f, glm::vec2(5.0f, 0.5f),
        collision1Normal, intersection1Depth)) {
        circle1Velocity += collision1Normal * -7.5f;

    }
    if (PhysicsUtils::IsCollidingRectRect(
        circle2Position, 0.0f, glm::vec2(0.5f),
        glm::vec2(0, 0), 0.0f, glm::vec2(5.0f, 0.5f),
        collision2Normal, intersection2Depth)) {
        circle2Velocity += collision2Normal * -3.5f;

    }
    if (PhysicsUtils::IsCollidingRectRect(
        circle3Position, 0.0f, glm::vec2(0.5f),
        glm::vec2(0, 0), 0.0f, glm::vec2(5.0f, 0.5f),
        collision3Normal, intersection3Depth)) {
        circle3Velocity += collision3Normal * -8.5f;

    }
    */

}

void HelloThere::Draw() {
    Draw::Circle(circle1Position, circle1Radius, true);
    Draw::Circle(circle2Position, circle2Radius, true);
    Draw::Circle(circle3Position, circle3Radius, true);

    // Up and Down
    Draw::Line(topLeft, topRight);
    Draw::Line(bottomLeft, bottomRight);

    // Left and Right
    Draw::Line(bottomLeft, topLeft);
    Draw::Line(bottomRight, topRight);

    DrawCube(circle1Position, circle1Radius);
    DrawCube(circle2Position, circle2Radius);
    DrawCube(circle3Position, circle3Radius);

}

// Unused
void HelloThere::DrawCube(glm::vec2 centerPoint, float circleRadius) {
    auto rectMat = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 2, 3, 4, 1);

    glm::vec2 center = glm::vec2(rectMat[3].x, rectMat[3].y);

    rectMat = glm::translate(glm::mat4(1.0f),
                             glm::vec3(centerPoint.x, centerPoint.y, 0));

    Draw::Rect(rectMat, glm::vec2(circleRadius), false);

}

void HelloThere::DrawGUI() {
    ImGui::Begin("Inspector");

    ImGui::DragFloat2("Circle 1 Position", &circle1Position[0], 0.1f);
    ImGui::DragFloat("Circle 1 Radius", &circle1Radius, 0.1f);

    ImGui::DragFloat2("Circle 2 Position", &circle2Position[0], 0.1f);
    ImGui::DragFloat("Circle 2 Radius", &circle2Radius, 0.1f);

    ImGui::DragFloat2("Circle 3 Position", &circle3Position[0], 0.1f);
    ImGui::DragFloat("Circle 3 Radius", &circle3Radius, 0.1f);

    ImGui::End();

}
