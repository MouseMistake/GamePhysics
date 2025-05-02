#include "Assignment2.h"

#include "imgui.h"
#include <core/Colors.h>
#include <iostream>

Assignment2::Assignment2()
    : circleRadius(1), circlePosition(circlePositionDefault), circleMass(5), circleVelocity(0) {};

void Assignment2::OnEnable() {
    // Kind of a hack because we need to press reset initially
    Reset();

    this->orthographicSize = 25.0f;

}

void Assignment2::OnDisable() {}

void Assignment2::Update(float deltaTime) {
    glm::vec2 baseForce(0.0f, -gravity.y);

    if ((circlePosition.y - forceFieldMin.y) < circleRadius) {
        glm::vec2 bottomScreenForce(2.0f, 100.0f);
        // totalAppliedForce = baseForce + bottomScreenForce * 0.3f;
    
    } else {
        // totalAppliedForce = baseForce;
    
    }
    totalAppliedForce = baseForce;

    AddForce(totalAppliedForce * circleMass);

    if (circlePosition.x + circleRadius > forceFieldMin.x &&
        circlePosition.y + circleRadius > forceFieldMin.y &&
        circlePosition.x - circleRadius < forceFieldMax.x &&
        circlePosition.y - circleRadius < forceFieldMax.y) {
        AddForce(forceFieldForce * circleMass);

    }

    circleAcceleration = totalAppliedForce / circleMass;
    totalAppliedForce = glm::vec2(0);

    // Capping the falling speed
    fallingSpeed = glm::length(circleVelocity);
    if (fallingSpeed > maxSpeed) {
        circleVelocity = glm::normalize(circleVelocity) * maxSpeed;

    }

    circleVelocity += circleAcceleration * deltaTime;
    circlePosition += circleVelocity * deltaTime;

}

void Assignment2::AddForce(glm::vec2 forceAmount) {
    totalAppliedForce += forceAmount;

}

void Assignment2::AddForcePush(glm::vec2 forceAmount) {
    circleVelocity += forceAmount;

}

void Assignment2::Reset() {
    circlePosition = circlePositionDefault;
    circleVelocity = glm::vec2(0);
    circleAcceleration = glm::vec2(0);

}

void Assignment2::Draw() {
    Draw::SetColor(Colors::red);
    Draw::AABB(forceFieldMin, forceFieldMax, false);

    Draw::SetColor(Colors::white);
    Draw::Circle(circlePosition, circleRadius, true);

}

void Assignment2::DrawGUI() {
    ImGui::Begin("Inspector");

    ImGui::DragFloat("Circle Radius", &circleRadius);
    ImGui::DragFloat("Circle Mass", &circleMass);
    ImGui::LabelText("Falling Speed", std::to_string(fallingSpeed).c_str());
    ImGui::LabelText("Y Position Circle", std::to_string(circlePosition.y).c_str());
    ImGui::LabelText("X Position Circle", std::to_string(circlePosition.x).c_str());

    if (ImGui::Button("Reset")) {
        Reset();

    }

    if (ImGui::Button("Slap To The Right")) {
        AddForcePush(glm::vec2(50.0f, 0.0f));

    }

    if (ImGui::Button("Slap To The Left")) {
        AddForcePush(glm::vec2(-50.0f, 0.0f));

    }

    ImGui::End();

}
