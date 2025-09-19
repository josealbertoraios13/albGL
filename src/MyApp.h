//
// Created by jose_alberto on 18/09/2025.
//

#ifndef ALBGL_MYAPP_H
#define ALBGL_MYAPP_H

#pragma once
#include "Core/Application.h"

class MyApp : public Application {
    public:
        void Start() override;
        void Update(float deltaTime) override;
};


#endif //ALBGL_MYAPP_H