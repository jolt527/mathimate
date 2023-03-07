#include "Triangle.h"
#include <GL/glew.h>
#include "glm/gtx/transform.hpp"
#include <algorithm>

Triangle::Triangle(ShaderProgram& shaderProgram, float color[], float startPosition[], float endPosition[])
: shaderProgram(shaderProgram) {
    std::copy(color, color + 3, this->color);
    std::copy(startPosition, startPosition + 3, this->startPosition);
    std::copy(endPosition, endPosition + 3, this->endPosition);

    float vertexData[] = {
        -0.2f, -0.2f, 0.0f,
         0.2f, -0.2f, 0.0f,
         0.0f,  0.2f, 0.0f
    };

    modelMatrixLocation = shaderProgram.getUniformLocation((char *)"modelMatrix");
    colorLocation = shaderProgram.getUniformLocation((char *)"color");

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
}

void Triangle::renderFrame(int frame, int lastFrame) {
    float interpolation = (float)frame / lastFrame;
    glm::vec3 translationAmount = glm::vec3(
        glm::mix(startPosition[0], endPosition[0], interpolation),
        glm::mix(startPosition[1], endPosition[1], interpolation),
        glm::mix(startPosition[2], endPosition[2], interpolation)
    );
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), translationAmount);

    shaderProgram.use();
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniform3fv(colorLocation, 1, &color[0]);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
