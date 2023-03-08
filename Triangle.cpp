#include "Triangle.h"
#include <GL/glew.h>
#include "glm/gtx/transform.hpp"
#include <algorithm>

Triangle::Triangle(ShaderProgram& shaderProgram, float color[], float initialPosition[], float initialScale[], float initialRotationDegrees)
: shaderProgram(shaderProgram) {
    std::copy(color, color + 3, this->color);

    glm::vec3 initialPositionVector = glm::vec3(initialPosition[0], initialPosition[1], initialPosition[2]);
    propertyIntervalManager.setInitialPosition(initialPositionVector);
    glm::vec3 initialScaleVector = glm::vec3(initialScale[0], initialScale[1], initialScale[2]);
    propertyIntervalManager.setInitialScaling(initialScaleVector);
    propertyIntervalManager.setInitialRotationDegrees(initialRotationDegrees);

    glm::vec3 startValue = initialPositionVector;
    glm::vec3 endValue = glm::vec3(-0.8f, 0.8f, 0.0f);
    propertyIntervalManager.addTranslationInterval(0, 59, startValue, endValue);

    propertyIntervalManager.addRotationInterval(30, 59, initialRotationDegrees, -45.0f, true);

    startValue = endValue;
    endValue = glm::vec3(0.8f, -0.8f, 0.0f);
    propertyIntervalManager.addTranslationInterval(60, 89, startValue, endValue);

    propertyIntervalManager.addRotationInterval(75, 89, -45.0f, 90.0f, false);

    propertyIntervalManager.addRotationInterval(90, 104, 90.0f, 115.0f, false);

    startValue = endValue;
    endValue = glm::vec3(0.0f, 0.8f, 0.0f);
    propertyIntervalManager.addTranslationInterval(105, 134, startValue, endValue);

    startValue = glm::vec3(1.0f, 1.0f, 1.0f);
    endValue = glm::vec3();
    propertyIntervalManager.addScalingInterval(110, 134, startValue, endValue);

    float vertexData[] = {
        0.0f,  0.1f, 0.0f,
        0.0f, -0.1f, 0.0f,
        0.4f,  0.0f, 0.0f
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
