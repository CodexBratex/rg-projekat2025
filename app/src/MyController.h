//
// Created by matfrg on 10/11/25.
//

#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H
#include "../../engine/libs/assimp/code/AssetLib/Collada/ColladaHelper.h"
#include "glm/vec3.hpp"

#include <engine/core/Controller.hpp>


class MyController : public engine::core::Controller {
    bool loop() override;
    void poll_events() override;
    void begin_draw() override;
    void draw() override;
    void end_draw() override;
    void initialize() override;
    void update() override;
    bool m_cursor_enabled{true};
    float x = 0;
    float y = 0;
    float z = 0;
    float timerEvent = 0;
    float angleRot = 0;
    public:
    glm::vec3 pointLightColor = glm::vec3(0.4f,0.5f,0.7f);
    glm::vec3 dirLightDirection = glm::vec3(0.0f,-1.0f,0.0f);
    glm::vec3 dirLightColor = glm::vec3(0.4f,0.4f,0.2f);
};



#endif //MYCONTROLLER_H
