//
// Created by Chase Nagle on 11/29/24.
//

#ifndef OPENGLPROJECT_GLOBALS_HPP
#define OPENGLPROJECT_GLOBALS_HPP






//Dont worry, however you can edit if you want to add new attributes
struct Vertex{
    float position[3];
    float normal[3];
    float color[3];
};

struct Vector3{
    float x;
    float y;
    float z;

    void Cross(Vector3 o){
        x = ( (y * o.z) - (z * o.y) );
        y = -((x*o.z)-(o.x * z));
        z = ((x * o.y) - (y * o.x));
    }

    void operator+=(const Vector3 &o){
        x += o.x;
        y += o.y;
        z += o.z;
    }

    void operator-=(const Vector3 &o){
        x -= o.x;
        y -= o.y;
        z -= o.z;
    }

};



#endif //OPENGLPROJECT_GLOBALS_HPP
