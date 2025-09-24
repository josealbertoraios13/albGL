//
// Created by jose_alberto on 23/09/2025.
//

#ifndef ALBGL_RECTANGLE_H
#define ALBGL_RECTANGLE_H
#include "Mesh.h"

using namespace std;

class Rectangle : public Mesh {
    private:
        string name;

    public:
        Rectangle();

        void SetName(const string &_name);
        string GetName();
};


#endif //ALBGL_RECTANGLE_H