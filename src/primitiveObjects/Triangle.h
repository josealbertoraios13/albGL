//
// Created by jose_alberto on 22/09/2025.
//

#ifndef ALBGL_TRIANGLE_H
#define ALBGL_TRIANGLE_H
#include "Mesh.h"

using namespace std;

class Triangle : public Mesh{
    private:
        string name;

    public:
        Triangle();

        void SetName(const string &_name);
        string GetName();
};


#endif //ALBGL_TRIANGLE_H