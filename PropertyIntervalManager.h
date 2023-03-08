#ifndef PROPERTY_INTERVAL_MANAGER_H
#define PROPERTY_INTERVAL_MANAGER_H

#include "glm/mat4x4.hpp"
#include <vector>

class PropertyIntervalManager {

public:

    void setInitialPosition(glm::vec3& initialPosition);
    void setInitialScaling(glm::vec3& initialScaling);

    void addTranslationInterval(int startFrame, int endFrame, glm::vec3& startPosition, glm::vec3 endPosition);
    void addScalingInterval(int startFrame, int endFrame, glm::vec3& startScale, glm::vec3 endScale);

    glm::mat4 calculateModelMatrix(int frame);

private:

    typedef struct TranslationInterval {
        int startFrame;
        int endFrame;
        glm::vec3 startPosition;
        glm::vec3 endPosition;
    } TranslationInterval;

    typedef struct ScalingInterval {
        int startFrame;
        int endFrame;
        glm::vec3 startScale;
        glm::vec3 endScale;
    } ScalingInterval;

    std::vector<TranslationInterval> translationIntervals;
    std::vector<ScalingInterval> scalingIntervals;

    glm::vec3 initialPosition;
    glm::vec3 initialScaling;

    glm::vec3 calculateTranslationAtFrame(int frame);
    glm::vec3 calculateScalingAtFrame(int frame);
};

#endif
