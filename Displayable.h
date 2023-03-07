#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

class Displayable {

public:

    virtual void renderFrame(int frame, int lastFrame) = 0;
};

#endif
