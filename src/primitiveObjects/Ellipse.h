//
// Created by jose_alberto on 23/09/2025.
//

#ifndef ALBGL_ELLIPSE_H
#define ALBGL_ELLIPSE_H
#include "Mesh.h"

using namespace std;

class Ellipse : public Mesh{
    public:
        Ellipse();

    protected:
        void Render() const override;
};


#endif //ALBGL_ELLIPSE_H