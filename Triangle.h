#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Displayable.h"
#include "ShaderProgram.h"
#include "PropertyIntervalManager.h"

class Triangle : public Displayable {

public:

    Triangle(ShaderProgram& shaderProgram, float color[], float initialPosition[]);

    void renderFrame(int frame);

private:

    float color[3];

    ShaderProgram& shaderProgram;
    GLuint vbo, vao;
    GLint modelMatrixLocation;
    GLint colorLocation;

    PropertyIntervalManager propertyIntervalManager;
};

#endif
