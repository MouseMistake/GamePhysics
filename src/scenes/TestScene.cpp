#include "TestScene.h"

#include "core/Draw.h"
#include "imgui.h"

TestScene::TestScene() : circlePosition(0, 1), circleRadius(1) {}

TestScene::~TestScene() {}

void TestScene::OnEnable() {

}

void TestScene::OnDisable() {}

void TestScene::Update(float deltaTime) {
       

}

void TestScene::Draw() {
    Draw::Circle(circlePosition, circleRadius, true);
    Draw::Line(glm::vec2(-5, 0), glm::vec2(5, 0));

}

void TestScene::DrawGUI() {
    ImGui::Begin("Inspector");
    ImGui::DragFloat2("Circle Position", &circlePosition[0], 0.1f);
    ImGui::DragFloat("Circle Radius", &circleRadius, 0.1f);
    ImGui::LabelText("", "My code under here.");
    ImGui::End();
}