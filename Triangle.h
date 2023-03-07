#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Displayable.h"
#include "ShaderProgram.h"

class Triangle : public Displayable {

public:

    Triangle(ShaderProgram& shaderProgram, float color[], float startPosition[], float endPosition[]);

    void renderFrame(int frame, int lastFrame);

private:

    float color[3];
    float startPosition[3];
    float endPosition[3];

    ShaderProgram& shaderProgram;
    GLuint vbo, vao;
    GLint modelMatrixLocation;
    GLint colorLocation;
};

#endif
