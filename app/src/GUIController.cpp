//
// Created by matfrg on 10/11/25.
//

#include "GUIController.h"

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
    graphics->begin_gui();
    {
        ImGui::Begin("Camera Info");
        ImGui::Text("Camera Position: (%f, %f, %f)", c->Position.x, c->Position.y, c->Position.z);
        ImGui::Text("(Yaw,Pitch): (%f, %f)", c->Yaw, c->Pitch);
        ImGui::End();
    }
    graphics->end_gui();
}
