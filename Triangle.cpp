#include "Triangle.h"
#include <GL/glew.h>
#include "glm/gtx/transform.hpp"
#include <algorithm>

Triangle::Triangle(ShaderProgram& shaderProgram, float color[], float initialPosition[])
: shaderProgram(shaderProgram) {
    std::copy(color, color + 3, this->color);

    glm::vec3 initialPositionVector = glm::vec3(initialPosition[0], initialPosition[1], initialPosition[2]);
    propertyIntervalManager.setInitialPosition(initialPositionVector);

    glm::vec3 startPositionVector = initialPositionVector;
    glm::vec3 endPositionVector = glm::vec3(0.0f, 0.8f, 0.0f);
    propertyIntervalManager.addTranslationInterval(0, 15, startPositionVector, endPositionVector);

    startPositionVector = endPositionVector;
    endPositionVector = glm::vec3(0.8f, -0.5f, 0.0f);
    propertyIntervalManager.addTranslationInterval(49, 59, startPositionVector, endPositionVector);

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

void Triangle::renderFrame(int frame) {
    glm::mat4 modelMatrix = propertyIntervalManager.calculateModelMatrix(frame);

    shaderProgram.use();
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniform3fv(colorLocation, 1, &color[0]);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
