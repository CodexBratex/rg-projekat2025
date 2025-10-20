//
// Created by matfrg on 10/11/25.
//

#include "GUIController.h"

#include "MyController.h"
#include "spdlog/spdlog.h"

#include <engine/graphics/GraphicsController.hpp>
#include <engine/platform/PlatformController.hpp>
#include <imgui.h>
void GUIController::initialize() {
    set_enable(false);
}
void GUIController::poll_events() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    if (platform->key(engine::platform::KeyId::KEY_F2).state() == engine::platform::Key::State::JustPressed) {
            set_enable(!is_enabled());
    }
}
void GUIController::draw() {
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    const auto &c = graphics->camera();
    auto pointColor = &engine::core::Controller::get<MyController>()->pointLightColor;
    auto dirDirection = &engine::core::Controller::get<MyController>()->dirLightDirection;
    auto dirColor =&engine::core::Controller::get<MyController>()->dirLightColor;
    graphics->begin_gui();
    {
        ImGui::Begin("Camera Info");
        ImGui::Text("Camera Position: (%f, %f, %f)", c->Position.x, c->Position.y, c->Position.z);
        ImGui::Text("(Yaw,Pitch): (%f, %f)", c->Yaw, c->Pitch);
        ImGui::DragFloat3("PointLight color",(float*)pointColor,0.01f,0.0f,1.0f,"%.2f");
        ImGui::DragFloat3("Direction of DirLight ",(float*)dirDirection,0.01f,-1.0f,1.0f,"%.2f");
        ImGui::DragFloat3("Dir Light color",(float*)dirColor,0.01f,0.0f,1.0f,"%.2f");
        ImGui::End();
    }
    graphics->end_gui();
}
