#include "PropertyIntervalManager.h"
#include "glm/gtx/transform.hpp"

void PropertyIntervalManager::setInitialPosition(glm::vec3& initialPosition) {
    this->initialPosition = initialPosition;
}

void PropertyIntervalManager::addTranslationInterval(int startFrame, int endFrame, glm::vec3& startPosition, glm::vec3 endPosition) {
    TranslationInterval newInterval = {startFrame, endFrame, startPosition, endPosition};
    translationIntervals.push_back(newInterval);
}

glm::mat4 PropertyIntervalManager::calculateModelMatrix(int frame) {
    glm::vec3 translation = calculateTranslationAtFrame(frame);

    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), translation);

    return modelMatrix;
}

glm::vec3 PropertyIntervalManager::calculateTranslationAtFrame(int frame) {
    glm::vec3 translation = initialPosition;

    int furthestEndFrameSeen = -1;
    for (TranslationInterval currentInterval : translationIntervals) {
        if (frame >= currentInterval.startFrame && frame <= currentInterval.endFrame) {
            float interpolation = (float)(frame - currentInterval.startFrame) / (currentInterval.endFrame - currentInterval.startFrame);
            translation =  glm::mix(currentInterval.startPosition, currentInterval.endPosition, interpolation);
            break;
        } else if (frame >= currentInterval.endFrame && currentInterval.endFrame > furthestEndFrameSeen) {
            translation = currentInterval.endPosition;
            furthestEndFrameSeen = currentInterval.endFrame;
        }
    }

    return translation;
}
