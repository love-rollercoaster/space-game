#pragma once
#include "camera.h"
#include "GameObject.h"
class FollowCamera :
    public Camera
{
public:
    FollowCamera(void);
    ~FollowCamera(void);
};

