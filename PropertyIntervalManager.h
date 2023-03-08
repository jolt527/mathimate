#ifndef PROPERTY_INTERVAL_MANAGER_H
#define PROPERTY_INTERVAL_MANAGER_H

#include "glm/mat4x4.hpp"
#include <vector>

class PropertyIntervalManager {

public:

    void setInitialPosition(glm::vec3& initialPosition);

    void addTranslationInterval(int startFrame, int endFrame, glm::vec3& startPosition, glm::vec3 endPosition);

    glm::mat4 calculateModelMatrix(int frame);

private:

    typedef struct TranslationInterval {
        int startFrame;
        int endFrame;
        glm::vec3 startPosition;
        glm::vec3 endPosition;
    } TranslationInterval;

    std::vector<TranslationInterval> translationIntervals;

    glm::vec3 initialPosition;

    glm::vec3 calculateTranslationAtFrame(int frame);
};

#endif
