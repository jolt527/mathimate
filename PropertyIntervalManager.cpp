#include "PropertyIntervalManager.h"
#include "glm/gtx/transform.hpp"

void PropertyIntervalManager::setInitialPosition(glm::vec3& initialPosition) {
    this->initialPosition = initialPosition;
}

void PropertyIntervalManager::setInitialScaling(glm::vec3& initialScaling) {
    this->initialScaling = initialScaling;
}

void PropertyIntervalManager::setInitialRotationDegrees(float initialRotationDegrees) {
    this->initialRotationDegrees = initialRotationDegrees;
}

void PropertyIntervalManager::addTranslationInterval(int startFrame, int endFrame, glm::vec3& startPosition, glm::vec3 endPosition) {
    TranslationInterval newInterval = { startFrame, endFrame, startPosition, endPosition };
    translationIntervals.push_back(newInterval);
}

void PropertyIntervalManager::addScalingInterval(int startFrame, int endFrame, glm::vec3& startScale, glm::vec3 endScale) {
    ScalingInterval newInterval = { startFrame, endFrame, startScale, endScale };
    scalingIntervals.push_back(newInterval);
}

void PropertyIntervalManager::addRotationInterval(int startFrame, int endFrame, float startRotationDegrees, float endRotationDegrees, bool rotateClockwise) {
    while (startRotationDegrees < 0.0f) {
        startRotationDegrees += 360.0f;
    }
    while (startRotationDegrees >= 360.0f) {
        startRotationDegrees -= 360.0f;
    }

    while (endRotationDegrees < 0.0f) {
        endRotationDegrees += 360.0f;
    }
    while (endRotationDegrees >= 360.0f) {
        endRotationDegrees -= 360.0f;
    }

    if (rotateClockwise && startRotationDegrees < endRotationDegrees) {
        startRotationDegrees += 360.0f;
    } else if (!rotateClockwise && startRotationDegrees > endRotationDegrees) {
        startRotationDegrees -= 360.0f;
    }

    RotationDegreesInterval newInterval = { startFrame, endFrame, startRotationDegrees, endRotationDegrees };
    rotationDegreesIntervals.push_back(newInterval);
}

glm::mat4 PropertyIntervalManager::calculateModelMatrix(int frame) {
    glm::vec3 scaling = calculateScalingAtFrame(frame);
    glm::vec3 translation = calculateTranslationAtFrame(frame);
    float rotationDegrees = calculateRotationDegreesAtFrame(frame);

    glm::mat4 modelMatrix =
        glm::translate(glm::mat4(1.0f), translation) *
        glm::rotate(glm::radians(rotationDegrees), glm::vec3(0, 0, 1)) *
        glm::scale(scaling)
    ;

    return modelMatrix;
}

glm::vec3 PropertyIntervalManager::calculateTranslationAtFrame(int frame) {
    glm::vec3 translation = initialPosition;

    int furthestEndFrameSeen = -1;
    for (TranslationInterval currentInterval : translationIntervals) {
        if (frame >= currentInterval.startFrame && frame <= currentInterval.endFrame) {
            float interpolation = (float)(frame - currentInterval.startFrame) / (currentInterval.endFrame - currentInterval.startFrame);
            translation = glm::mix(currentInterval.startPosition, currentInterval.endPosition, interpolation);
            break;
        } else if (frame >= currentInterval.endFrame && currentInterval.endFrame > furthestEndFrameSeen) {
            translation = currentInterval.endPosition;
            furthestEndFrameSeen = currentInterval.endFrame;
        }
    }

    return translation;
}

glm::vec3 PropertyIntervalManager::calculateScalingAtFrame(int frame) {
    glm::vec3 scaling = initialScaling;

    int furthestEndFrameSeen = -1;
    for (ScalingInterval currentInterval : scalingIntervals) {
        if (frame >= currentInterval.startFrame && frame <= currentInterval.endFrame) {
            float interpolation = (float)(frame - currentInterval.startFrame) / (currentInterval.endFrame - currentInterval.startFrame);
            scaling = glm::mix(currentInterval.startScale, currentInterval.endScale, interpolation);
            break;
        } else if (frame >= currentInterval.endFrame && currentInterval.endFrame > furthestEndFrameSeen) {
            scaling = currentInterval.endScale;
            furthestEndFrameSeen = currentInterval.endFrame;
        }
    }

    return scaling;
}

float PropertyIntervalManager::calculateRotationDegreesAtFrame(int frame) {
    float rotationDegrees = initialRotationDegrees;

    int furthestEndFrameSeen = -1;
    for (RotationDegreesInterval currentInterval : rotationDegreesIntervals) {
        if (frame >= currentInterval.startFrame && frame <= currentInterval.endFrame) {
            float interpolation = (float)(frame - currentInterval.startFrame) / (currentInterval.endFrame - currentInterval.startFrame);
            rotationDegrees = glm::mix(currentInterval.startRotationDegrees, currentInterval.endRotationDegrees, interpolation);
            break;
        } else if (frame >= currentInterval.endFrame && currentInterval.endFrame > furthestEndFrameSeen) {
            rotationDegrees = currentInterval.endRotationDegrees;
            furthestEndFrameSeen = currentInterval.endFrame;
        }
    }

    return rotationDegrees;
}
