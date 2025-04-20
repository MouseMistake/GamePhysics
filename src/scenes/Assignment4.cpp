#include "Assignment4.h"

#include "imgui.h"
#include <iostream>

Assignment4::Assignment4() {}
Assignment4::~Assignment4() {}

void Assignment4::OnEnable() {
    // Getting and normalizing the normal of the half space
    lineNormal = glm::normalize(GetLineNormal(groundStart, groundEnd));

    mainCircle = {
        glm::vec2(3, 4),
        1.0f,
        1.0f,
        glm::vec2(0, 0),
        glm::vec2(0, 0)
    };

}

void Assignment4::OnDisable() {}

void Assignment4::Update(float dt) {
    // General "falling ball" things
    mainCircle.force += gravity * mainCircle.mass;

    mainCircle.vel += (mainCircle.force / mainCircle.mass) * dt;

    mainCircle.pos += mainCircle.vel * dt;

    mainCircle.force = glm::vec2(0);

    // Calculating the distance from the circle to the half space
    projectedDistance = glm::dot(mainCircle.pos, lineNormal) - mainCircle.radius;

    if (projectedDistance < 0) {
        mainCircle.pos -= lineNormal * projectedDistance;

        // 0.8f is simply the resitution. It appears once so I kept it manual,
        // but it could be made a variable of course.
        mainCircle.vel = glm::reflect(mainCircle.vel, lineNormal) * 0.8f;
    
    }
        
    // Adding an invisible ground for the ball to bounce on
    if (mainCircle.pos.y - mainCircle.radius < -5.0f) {
        mainCircle.pos.y = -5.0f + mainCircle.radius;
        mainCircle.vel.y *= -0.76f;
    }

}

void Assignment4::Draw() {
    // Drawing the ground, center of which being origin
    Draw::Line(groundStart, groundEnd);

    // Drawing a small circle as a point to confirm the line's origin
    glm::vec2 lineCenter(groundEnd + groundStart);
    Draw::Circle(lineCenter, 0.12f, true);

    Draw::Circle(mainCircle.pos, mainCircle.radius, false);

}

void Assignment4::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::End();
}

glm::vec2 Assignment4::GetLineNormal(glm::vec2 lineStart, glm::vec2 lineEnd) {
    float deltaX = lineEnd.x - lineStart.x;
    float deltaY = lineEnd.y - lineStart.y;

    return glm::vec2(-deltaY, deltaX);

}
