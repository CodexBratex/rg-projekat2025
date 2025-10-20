//
// Created by matfrg on 10/11/25.
//

#include "MyController.h"
#include "GUIController.h"
#include "spdlog/spdlog.h"

#include <engine/graphics/GraphicsController.hpp>
#include <engine/graphics/OpenGL.hpp>
#include <engine/platform/PlatformController.hpp>
#include <engine/resources/ResourcesController.hpp>
void MyController::initialize() {
    engine::graphics::OpenGL::enable_depth_testing();
}
bool MyController::loop() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();

    if (platform->key(engine::platform::KeyId::KEY_ESCAPE).state() == engine::platform::Key::State::JustPressed) {
        return false;
    }
    return true;
}
void MyController::update() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
    float dt = platform->dt();
    if (platform->key(engine::platform::KEY_UP).state() == engine::platform::Key::State::Pressed) {
        y+=dt;
    }
    if (platform->key(engine::platform::KEY_DOWN).state() == engine::platform::Key::State::Pressed) {
        y-=dt;
    }
    if (platform->key(engine::platform::KEY_LEFT).state() == engine::platform::Key::State::Pressed) {
        x-=dt;
    }
    if (platform->key(engine::platform::KEY_RIGHT).state() == engine::platform::Key::State::Pressed) {
        x+=dt;
    }if (platform->key(engine::platform::KEY_PAGE_UP).state() == engine::platform::Key::State::Pressed) {
        z-=dt;
    }
    if (platform->key(engine::platform::KEY_PAGE_DOWN).state() == engine::platform::Key::State::Pressed) {
        z+=dt;
    }
    if(timerEvent<10.0f && timerEvent>7.0f) {
        angleRot=90*sin(glm::radians(30*(10-timerEvent)));
    }
    if(timerEvent<4.0f && timerEvent>1.0f) {
        angleRot=90*cos(glm::radians(30*(3-(timerEvent-1))));
    }
    timerEvent-=dt;
    auto gui = engine::core::Controller::get<GUIController>();
    if (gui->is_enabled()) {
        return;
    }
    if (platform->key(engine::platform::KEY_W).state() == engine::platform::Key::State::Pressed) {
        camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt);
    }
    if (platform->key(engine::platform::KEY_S).state() == engine::platform::Key::State::Pressed) {
        camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt);
    }
    if (platform->key(engine::platform::KEY_A).state() == engine::platform::Key::State::Pressed) {
        camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt);
    }
    if (platform->key(engine::platform::KEY_D).state() == engine::platform::Key::State::Pressed) {
        camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt);
    }
    auto mouse = platform->mouse();
    camera->rotate_camera(mouse.dx, mouse.dy);
    camera->zoom(mouse.scroll);
}
void MyController::poll_events() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    if (platform->key(engine::platform::KEY_F1).state() == engine::platform::Key::State::JustPressed) {
        m_cursor_enabled = !m_cursor_enabled;
        platform->set_enable_cursor(m_cursor_enabled);
    }
    if (platform->key(engine::platform::KEY_ENTER).state() == engine::platform::Key::State::JustPressed) {
        timerEvent=13.0f;
    }
}
void MyController::begin_draw() {
    engine::graphics::OpenGL::clear_buffers();
}
void MyController::draw() {
    auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
    struct DirLight {
        glm::vec3 direction;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };
    struct PointLight {
        glm::vec3 position;

        float constant;
        float linear;
        float quadratic;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto shader = engine::core::Controller::get<engine::resources::ResourcesController>()->shader("axe");
    auto axe = engine::core::Controller::get<engine::resources::ResourcesController>()->model("axe");
    auto cube = engine::core::Controller::get<engine::resources::ResourcesController>()->model("cube");
    PointLight pointLight;
    pointLight.position=glm::vec3(x,y,z);

    pointLight.ambient=0.08f*pointLightColor;
    pointLight.diffuse=pointLightColor;
    pointLight.specular=glm::vec3(1.0f,1.0f,1.0f);
    pointLight.constant=1.0f;
    pointLight.linear=0.09f;
    pointLight.quadratic=0.0067f;
    DirLight dirLight;
    dirLight.direction=dirLightDirection;
    dirLight.ambient=0.08f*dirLightColor;
    dirLight.diffuse=dirLightColor;
    dirLight.specular=glm::vec3(1.0f,1.0f,1.0f);
    shader->use();
    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());
    auto model = glm::mat4(1.0f);
    model = glm::translate(model,glm::vec3(0.0f,0.0f,-1.0f));
    model = glm::rotate(model,-glm::radians(angleRot),glm::vec3(0,0,1));
    shader->set_mat4("model", model);

    shader->set_vec3("pointLight.position",pointLight.position);
    shader->set_vec3("pointLight.ambient",pointLight.ambient);
    shader->set_vec3("pointLight.diffuse",pointLight.diffuse);
    shader->set_vec3("pointLight.specular",pointLight.specular);
    shader->set_float("pointLight.constant",pointLight.constant);
    shader->set_float("pointLight.linear",pointLight.linear);
    shader->set_float("pointLight.quadratic",pointLight.quadratic);

    shader->set_vec3("dirLight.direction",dirLight.direction);
    shader->set_vec3("dirLight.ambient",dirLight.ambient);
    shader->set_vec3("dirLight.diffuse",dirLight.diffuse);
    shader->set_vec3("dirLight.specular",dirLight.specular);

    shader->set_vec3("ViewPos",camera->Position);
    axe->draw(shader);
    auto shader2 = engine::core::Controller::get<engine::resources::ResourcesController>()->shader("cube");
    shader2->use();
    shader2->set_mat4("projection", graphics->projection_matrix());
    shader2->set_mat4("view", graphics->camera()->view_matrix());
    model = glm::mat4(1.0f);
    model = glm::translate(model,pointLight.position);
    model = glm::scale(model,glm::vec3(0.1f));
    shader2->set_mat4("model", model);
    shader2->set_vec3("color",pointLightColor);
    cube->draw(shader2);
}
void MyController::end_draw() {
    engine::core::Controller::get<engine::platform::PlatformController>()->swap_buffers();
}