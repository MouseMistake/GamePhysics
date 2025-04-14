#include "Assignment3.h"

#include "imgui.h"

Assignment3::Assignment3() : isMouseDown(false), selectedCircle(-1) {}

Assignment3::~Assignment3() {}

void Assignment3::OnEnable() {
    // Circle definitions
    auto circle1 = Circle{
        glm::vec2(0, 0), // Position
        1.0f, // Radius
        1.0f, // Mass
        glm::vec2(0, 0), // Current velocity
        glm::vec2(0, 0) // Current force

    };
    circles.push_back(circle1);

    auto circle2 = Circle{
        glm::vec2(5, 0),
        0.7f,
        2.75f,
        glm::vec2(0, 0),
        glm::vec2(0, 0)

    };
    circles.push_back(circle2);

    auto circle3 = Circle{
        glm::vec2(-5, 0),
        1.2f,
        1.5f,
        glm::vec2(0, 0),
        glm::vec2(0, 0)

    };
    circles.push_back(circle3);

}

void Assignment3::OnDisable() {}

void Assignment3::Update(float dt) {
    ReadMouseInput();

    if (isMouseDown && selectedCircle != -1) {
        circlePathPositions.clear();

        const Circle& circ = circles[selectedCircle];
        glm::vec2 pos = circ.pos;
        glm::vec2 vel = impulse / circ.mass;

        float maxTime = 10.0f;
        float currTime = 0.0f;

        while (currTime < maxTime) {
            circlePathPositions.push_back(pos);

            // Mulitplying dt by 6 because uh the circles are more readable idk it's visually nice
            vel += gravity * (dt * 6);
            pos += vel * (dt * 6);

            currTime += (dt * 6);

        }
    
    } else {
        for (auto& circ : circles) {
            Draw::Circle(circ.pos, circ.radius, true);

            circ.force += gravity * circ.mass;

            circ.vel += (circ.force / circ.mass) * dt;

            circ.pos += circ.vel * dt;

            circ.force = glm::vec2(0);

            if (circ.pos.y - circ.radius < -5.0f) {
                circ.pos.y = -5.0f + circ.radius;
                circ.vel.y *= -0.76f;

            }

        }

    }

}

void Assignment3::Draw() {
    // Ground
    Draw::Line(glm::vec2(-10, -5), glm::vec2(10, -5));
    
    // Drawing the bouncy balls
    for (auto& circ : circles) {
        Draw::Circle(circ.pos, circ.radius, true);
        
    }

    // If we're dragging a ball, drawing a line in the direction to which we want
    // to slap the ball
    if (isMouseDown && selectedCircle != -1) {
        // Getting the beginning and the end of the impulse vector
        glm::vec2 start = circles[selectedCircle].pos;
        glm::vec2 end = start + impulse;

        Draw::Line(start, end);
        Draw::Circle(end, 0.1f, false);

        if (circlePathPositions.size() > 0) {
            for (auto& point : circlePathPositions) {
                Draw::Circle(point, 0.3f, false);
            
            }
        
        }

    }

}

void Assignment3::DrawGUI() {
    ImGui::Begin("Inspector");

    ImGui::LabelText("Is Dragging?", std::to_string(isMouseDown).c_str());
    ImGui::LabelText("Selected Circle", std::to_string(selectedCircle).c_str());

    if (ImGui::Button("Reset")) {
        // Resets the vector of circles
        for (auto& circ : circles) {
            circ = {};
        
        }
        OnEnable();
        isMouseDown = false;
        selectedCircle = -1;
    
    }

    ImGui::End();
}

void Assignment3::ReadMouseInput() {
    // If we click
    if (Input::IsMouseClicked(ImGuiMouseButton_Left)) {
        glm::vec2 mousePos = Input::GetMousePos();

        for (int i = 0; i < circles.size(); i++) {
            float dist = glm::length(mousePos - circles[i].pos);

            if (dist <= circles[i].radius) {
                isMouseDown = true;
                selectedCircle = i;
                baseDragPosition = mousePos;
                break;

            }

        }
    
    }

    if (Input::IsMouseDown(ImGuiMouseButton_Left) && isMouseDown) {
        glm::vec2 mousePos = Input::GetMousePos();

        // Measures the distance there
        impulse = baseDragPosition - mousePos;

    }

    // When the mouse button is released, we unleash the power onto the ball (don't quote me on that)
    if (Input::IsMouseReleased(ImGuiMouseButton_Left) && isMouseDown) {
        // We check against -1 to make sure we're not applying the impulse onto nothing
        if (selectedCircle != -1) {
            circles[selectedCircle].vel += impulse / circles[selectedCircle].mass;

        }
        isMouseDown = false;
        selectedCircle = -1;

    }

}
