//
// Created by jose_alberto on 19/09/2025.
//

#ifndef ALBGL_TRANSFORM_H
#define ALBGL_TRANSFORM_H

#pragma once

#include "Vector3.h"

class Transform {
    public:
        Vector3 position;
        Vector3 rotation; //Em graus
        Vector3 scale;

        Transform();
};


#endif //ALBGL_TRANSFORM_H