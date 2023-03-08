#ifndef PROPERTY_INTERVAL_MANAGER_H
#define PROPERTY_INTERVAL_MANAGER_H

#include "glm/mat4x4.hpp"
#include <vector>

class PropertyIntervalManager {

public:

    void setInitialPosition(glm::vec3& initialPosition);
    void setInitialScaling(glm::vec3& initialScaling);
    void setInitialRotationDegrees(float initialRotationDegrees);

    void addTranslationInterval(int startFrame, int endFrame, glm::vec3& startPosition, glm::vec3 endPosition);
    void addScalingInterval(int startFrame, int endFrame, glm::vec3& startScale, glm::vec3 endScale);
    void addRotationInterval(int startFrame, int endFrame, float startRotationDegrees, float endRotationDegrees, bool rotateClockwise);

    glm::mat4 calculateModelMatrix(int frame);

private:

    typedef struct {
        int startFrame;
        int endFrame;
        glm::vec3 startPosition;
        glm::vec3 endPosition;
    } TranslationInterval;

    typedef struct {
        int startFrame;
        int endFrame;
        glm::vec3 startScale;
        glm::vec3 endScale;
    } ScalingInterval;

    typedef struct {
        int startFrame;
        int endFrame;
        float startRotationDegrees;
        float endRotationDegrees;
    } RotationDegreesInterval;

    std::vector<TranslationInterval> translationIntervals;
    std::vector<ScalingInterval> scalingIntervals;
    std::vector<RotationDegreesInterval> rotationDegreesIntervals;

    glm::vec3 initialPosition;
    glm::vec3 initialScaling;
    float initialRotationDegrees;

    glm::vec3 calculateTranslationAtFrame(int frame);
    glm::vec3 calculateScalingAtFrame(int frame);
    float calculateRotationDegreesAtFrame(int frame);
};

#endif
