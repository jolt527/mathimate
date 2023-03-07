#include "Triangle.h"
#include <GL/glew.h>

Triangle::Triangle(ShaderProgram& shaderProgram, float color[], float startPosition[], float endPosition[])
: shaderProgram(shaderProgram) {
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->startPosition[0] = startPosition[0];
    this->startPosition[1] = startPosition[1];
    this->startPosition[2] = startPosition[2];
    this->endPosition[0] = endPosition[0];
    this->endPosition[1] = endPosition[1];
    this->endPosition[2] = endPosition[2];

    float vertexData[] = {
        -0.2f, -0.2f, 0.0f,
         0.2f, -0.2f, 0.0f,
         0.0f,  0.2f, 0.0f
    };

    positionLocation = shaderProgram.getUniformLocation("position");
    colorLocation = shaderProgram.getUniformLocation("color");

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
}

void Triangle::renderFrame(int frame, int totalFrames) {
    float interpolation = (float)frame / totalFrames;
    float positionX = lerp(startPosition[0], endPosition[0], interpolation);
    float positionY = lerp(startPosition[1], endPosition[1], interpolation);
    float positionZ = lerp(startPosition[2], endPosition[2], interpolation);

    shaderProgram.use();
    glUniform3f(positionLocation, positionX, positionY, positionZ);
    glUniform3f(colorLocation, color[0], color[1], color[2]);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

float Triangle::lerp(float a, float b, float t) {
    return a + t * (b - a);
}
