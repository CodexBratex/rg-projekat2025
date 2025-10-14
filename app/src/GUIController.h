//
// Created by matfrg on 10/11/25.
//

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include <engine/core/Controller.hpp>


class GUIController : public engine::core::Controller {
    void poll_events() override;
    void draw() override;
    void initialize() override;
};



#endif //CAMERACONTROLLER_H
