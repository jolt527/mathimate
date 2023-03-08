#include "Triangle.h"
#include <GL/glew.h>
#include "glm/gtx/transform.hpp"
#include <algorithm>

Triangle::Triangle(ShaderProgram& shaderProgram, float color[], float initialPosition[], float initialScale[])
: shaderProgram(shaderProgram) {
    std::copy(color, color + 3, this->color);

    glm::vec3 initialPositionVector = glm::vec3(initialPosition[0], initialPosition[1], initialPosition[2]);
    propertyIntervalManager.setInitialPosition(initialPositionVector);
    glm::vec3 initialScaleVector = glm::vec3(initialScale[0], initialScale[1], initialScale[2]);
    propertyIntervalManager.setInitialScaling(initialScaleVector);

    glm::vec3 startValue = initialPositionVector;
    glm::vec3 endValue = glm::vec3(0.25f, 0.25f, 0.0f);
    propertyIntervalManager.addTranslationInterval(0, 59, startValue, endValue);

    startValue = glm::vec3(1.0f, 1.0f, 1.0f);
    endValue = glm::vec3(2.0f, 2.0f, 2.0f);
    propertyIntervalManager.addScalingInterval(60, 89, startValue, endValue);

    startValue = glm::vec3(2.0f, 2.0f, 2.0f);
    endValue = glm::vec3(1.0f, 1.0f, 1.0f);
    propertyIntervalManager.addScalingInterval(90, 119, startValue, endValue);

    startValue = glm::vec3(0.25f, 0.25f, 0.0f);
    endValue = glm::vec3(1.0f, -1.0f, 0.0f);
    propertyIntervalManager.addTranslationInterval(120, 179, startValue, endValue);

    startValue = glm::vec3(1.0f, 1.0f, 1.0f);
    endValue = glm::vec3(0.0f, 0.0f, 1.0f);
    propertyIntervalManager.addScalingInterval(120, 179, startValue, endValue);

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
