#include "GUIController.h"
#include "MyController.h"
#include "spdlog/spdlog.h"


#include <engine/core/Engine.hpp>

class MyApp : public engine::core::App {
    void app_setup() override;
};

void MyApp::app_setup() {
    spdlog::info("Setup Complete!");
    auto MyController = register_controller<::MyController>();
    auto GUIController = register_controller<::GUIController>();
    MyController->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());
    GUIController->after(MyController);
}


int main(int argc, char** argv) {
    return std::make_unique<MyApp>()->run(argc,argv);
}
