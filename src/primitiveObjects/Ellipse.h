//
// Created by jose_alberto on 23/09/2025.
//

#ifndef ALBGL_ELLIPSE_H
#define ALBGL_ELLIPSE_H
#include "Mesh.h"

using namespace std;

class Ellipse : public Mesh{
    private:
        string name;

    public:
        Ellipse();

        void SetName(const string &_name);
        string GetName();private:

    protected:
        void Render() const override;
};


#endif //ALBGL_ELLIPSE_H