#pragma once
class InputComponent
{
public:
    InputComponent(void);
    ~InputComponent(void);

    virtual void update(GameObject &gameObject, time_t time) = 0;
};