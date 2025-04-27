#include "Assignment5.h"

#include "imgui.h"

Assignment5::Assignment5() : isMouseDown(false), selectedCircle(-1), howManyDropped(0) {}
Assignment5::~Assignment5() {}

void Assignment5::OnEnable() {
    // Overloads the protected variables from Simple2DScene
    // This avoids having to zoom out everytime we load the scene
    this->orthographicSize = 35;
    this->cameraCenter = glm::vec2(10, 15);

    // Making the cue ball
    cueBall = {
        glm::vec2(10, 5),
        ballRadius,
        ballMass,
        glm::vec2(0, 0),
        glm::vec2(0, 0),
        0.0f,
        0,
        false
    };

    // 15 balls. You know, I'm learning a lot about pool
    // Starting at 1 because 0 is reserved for the cue ball
    for (uint8_t i = 1; i <= 15; i++) {
        Circle ball = {
            glm::vec2(0, 0),
            ballRadius,
            ballMass,
            glm::vec2(0, 0),
            glm::vec2(0, 0),
            0.0f,
            i,
            false
        }; 
        poolBalls.push_back(ball);

    }

    AssignBallPositions();

    // Building the boundaries of the pool table
    // Keeping the values positive or it'd be a mess with normals and yuck
    auto wallsLeft = Wall{glm::vec2(0, 30), glm::vec2(0, 0), glm::vec2(0)};
    auto wallsRight = Wall{glm::vec2(20, 30), glm::vec2(20, 0), glm::vec2(0)};
    auto wallsUp = Wall{glm::vec2(0, 30), glm::vec2(20, 30), glm::vec2(0)};
    auto wallsDown = Wall{glm::vec2(0, 0), glm::vec2(20, 0), glm::vec2(0)};

    // Flipping the normals for the wall on the right and up to reflect inside
    wallsLeft.lineNormal = GetLineNormal(wallsLeft.startPoint, wallsLeft.endPoint);
    wallsRight.lineNormal = -GetLineNormal(wallsRight.startPoint, wallsRight.endPoint);
    wallsUp.lineNormal = -GetLineNormal(wallsUp.startPoint, wallsUp.endPoint);
    wallsDown.lineNormal = GetLineNormal(wallsDown.startPoint, wallsDown.endPoint);

    poolWalls.push_back(wallsLeft);
    poolWalls.push_back(wallsRight);
    poolWalls.push_back(wallsUp);
    poolWalls.push_back(wallsDown);

    // The 6 pool holes for the balls to "fall" into
    poolHoles = {
        Hole{glm::vec2(0, 0), 1.5f, 0},
        Hole{glm::vec2(0, 15), 1.5f, 1},
        Hole{glm::vec2(0, 30), 1.5f, 2},
        Hole{glm::vec2(20, 0), 1.5f, 3},
        Hole{glm::vec2(20, 15), 1.5f, 4},
        Hole{glm::vec2(20, 30), 1.5f, 5}

    };

}

void Assignment5::OnDisable() {}

void Assignment5::Update(float deltaTime) {
    ReadMouseInput();
    UpdateCueBall(deltaTime);

    TestWallCollision(cueBall);

    for (auto& ball : poolBalls) {
        if (ball.hasDropped) continue;
        TestWallCollision(ball);

        ball.vel += (ball.force / ball.mass) * deltaTime;

        ball.pos += ball.vel * deltaTime;

        // Dirty illusion, no idea if that's actually how you do it
        glm::vec2 fakeDrag = -(ball.vel * 0.8f);

        ball.force = glm::vec2(fakeDrag);

        for (auto& hole : poolHoles) {
            if (glm::distance(ball.pos, hole.pos) < (ball.radius + hole.radius)) {
                ball.hasDropped = true;
                howManyDropped++;

            }
        
        }

        // I love CPU cycles!!
        // This went haywire, it didn't quite work, so I'm letting go for now
        /*
        for (auto& ballOther : poolBalls) {
            if (glm::distance(ball.pos, ballOther.pos) < (ball.radius + ballOther.radius)) {
                glm::vec2 direction = glm::normalize(ballOther.pos - ball.pos);

                glm::vec2 resolve = direction * ((ball.radius + ballOther.radius) - glm::distance(ball.pos, ballOther.pos) / 2.0f);

                ball.vel -= resolve;
                ballOther.vel += resolve;

            }

        }
        */
    
    }
    
}

void Assignment5::Draw() {
    // Drawing the table
    for (auto& wall : poolWalls) {
        Draw::Line(wall.startPoint, wall.endPoint);

    }

    // Drawing the holes of the table
    for (auto& hole : poolHoles) {
        Draw::Circle(hole.pos, hole.radius, true);

    }

    // Cue ball
    Draw::Circle(cueBall.pos, cueBall.radius, true);

    // Drawing the table
    for (auto& ball : poolBalls) {
        if (ball.hasDropped) continue;

        Draw::Circle(ball.pos, ball.radius, false);

        // Adding half radius to the position of the text as a sad attempt to center it
        Draw::Text(ball.pos + glm::vec2((-ball.radius / 2), ball.radius / 2), std::to_string(ball.id).c_str());

    }

    // If we're dragging a ball, drawing a line in the direction to which we
    // want to slap the ball
    if (isMouseDown && selectedCircle == 0) {
        // Getting the beginning and the end of the impulse vector
        glm::vec2 start = cueBall.pos;
        glm::vec2 end = start + impulse;

        Draw::Line(start, end);
        Draw::Circle(end, 0.1f, false);

    }

}

void Assignment5::DrawGUI() {
    ImGui::Begin("Inspector");

    ImGui::LabelText("Is Dragging?", std::to_string(isMouseDown).c_str());
    ImGui::LabelText("Selected Circle", std::to_string(selectedCircle).c_str());

    ImGui::LabelText("Balls Dropped", std::to_string(howManyDropped).c_str());

    if (ImGui::Button("Reset")) {
        // Resets everything
        poolBalls.clear();
        poolWalls.clear();

        cueBall = {};
        OnEnable();
        isMouseDown = false;
        selectedCircle = -1;
    }

    ImGui::End();
}

void Assignment5::ReadMouseInput() {
    // If we click
    if (Input::IsMouseClicked(ImGuiMouseButton_Left)) {
        glm::vec2 mousePos = Input::GetMousePos();

        // For the cue ball
        float dist = glm::length(mousePos - cueBall.pos);

        if (dist <= cueBall.radius) {
            isMouseDown = true;
            selectedCircle = cueBall.id;
            baseDragPosition = mousePos;
            
        } else {
            // Figuring out which ball we just clicked on
            for (auto& ball : poolBalls) {
                float dist = glm::length(mousePos - ball.pos);

                if (dist <= ball.radius) {
                    isMouseDown = true;
                    selectedCircle = ball.id;
                    baseDragPosition = mousePos;
                    break;
                }
            }

        }

    }

    if (Input::IsMouseDown(ImGuiMouseButton_Left) && isMouseDown) {
        glm::vec2 mousePos = Input::GetMousePos();

        // Measures the distance there
        impulse = baseDragPosition - mousePos;

    }

    // When the mouse button is released, we unleash the power onto the ball
    // (don't quote me on that)
    if (Input::IsMouseReleased(ImGuiMouseButton_Left) && isMouseDown) {
        // We only want to be able to impulse onto the cue ball you get me?
        if (selectedCircle == 0) {
            cueBall.vel += impulse / cueBall.mass;

        }
        isMouseDown = false;
        selectedCircle = -1;

    }
}

void Assignment5::UpdateCueBall(float dt) {
    cueBall.vel += (cueBall.force / cueBall.mass) * dt;

    cueBall.pos += cueBall.vel * dt;
    
    // Dirty illusion, no idea if that's actually how you do it
    glm::vec2 fakeDrag = -(cueBall.vel * 0.8f);

    cueBall.force = glm::vec2(fakeDrag);

    for (auto& ball : poolBalls) {
        if (glm::distance(cueBall.pos, ball.pos) < (cueBall.radius + ball.radius)) {
            glm::vec2 direction = glm::normalize(ball.pos - cueBall.pos);

            glm::vec2 resolve = direction * ((cueBall.radius + ball.radius) - glm::distance(cueBall.pos, ball.pos) / 2.0f);

            cueBall.vel -= resolve;
            ball.vel += resolve;
        
        }
    
    }

}

void Assignment5::TestWallCollision(Circle& ball) {
    // For each pool wall
    for (auto& wall : poolWalls) {
        // Calculating the distance from the ball to the half space
        ball.projectedDistance = glm::dot(ball.pos - wall.startPoint, wall.lineNormal) - ball.radius;

        if (ball.projectedDistance < 0) {
            ball.pos -= wall.lineNormal * ball.projectedDistance;

            // 0.8f is simply the resitution. It appears once so I kept it
            // manual, but it could be made a variable of course.
            ball.vel = glm::reflect(ball.vel, wall.lineNormal) * 0.8f;

        }
    
    }

}

void Assignment5::AssignBallPositions() {
    // Yeah this is super manual, but not the main point
    // of the assignment so it's fine
    for (auto& ball : poolBalls) {
        switch (ball.id) {
            case 1:
                ball.pos = glm::vec2(10, 20);
                break;
            case 2:
                ball.pos = glm::vec2(11, 22);
                break;
            case 3:
                ball.pos = glm::vec2(9, 22);
                break;
            case 4:
                ball.pos = glm::vec2(12, 24);
                break;
            case 5:
                ball.pos = glm::vec2(10, 24);
                break;
            case 6:
                ball.pos = glm::vec2(8, 24);
                break;
            case 7:
                ball.pos = glm::vec2(13, 26);
                break;
            case 8:
                ball.pos = glm::vec2(11, 26);
                break;
            case 9:
                ball.pos = glm::vec2(9, 26);
                break;
            case 10:
                ball.pos = glm::vec2(7, 26);
                break;
            case 11:
                ball.pos = glm::vec2(14, 28);
                break;
            case 12:
                ball.pos = glm::vec2(12, 28);
                break;
            case 13:
                ball.pos = glm::vec2(10, 28);
                break;
            case 14:
                ball.pos = glm::vec2(8, 28);
                break;
            case 15:
                ball.pos = glm::vec2(6, 28);
                break;

        }

    }

}

glm::vec2 Assignment5::GetLineNormal(glm::vec2 lineStart, glm::vec2 lineEnd) {
    float deltaX = lineEnd.x - lineStart.x;
    float deltaY = lineEnd.y - lineStart.y;

    glm::vec2 normal(-deltaY, deltaX);
    normal = glm::normalize(normal);

    if (normal.x < 0) normal.x = -normal.x;
    if (normal.y < 0) normal.y = -normal.y;

    return normal;

}
