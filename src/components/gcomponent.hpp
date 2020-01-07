#ifndef COMPONENT_H
#define COMPONENT_H

struct GComponent {
    // init a Component
    virtual bool init() = 0;
};

#endif