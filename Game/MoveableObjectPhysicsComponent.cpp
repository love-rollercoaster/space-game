#include "MoveableObjectPhysicsComponent.h"


MoveableObjectPhysicsComponent::MoveableObjectPhysicsComponent(void)
{
}


MoveableObjectPhysicsComponent::~MoveableObjectPhysicsComponent(void)
{
}

void MoveableObjectPhysicsComponent::update(GameObject &gameObject, float time)
{
    MoveableGameObject *moveableGameObject = dynamic_cast<MoveableGameObject*>(&gameObject);
    
    if (moveableGameObject == NULL) {
        throw "This component only works with MoveableGameObjects!";
    }
    updatePosition(*moveableGameObject, time);
    updateRotationSpeeds(*moveableGameObject, time);
}

void MoveableObjectPhysicsComponent::updateRotationSpeeds(MoveableGameObject &obj, float time )
{
    float timeInMilliseconds = time / 1000.0f;

    obj.roll(obj.getRollRotationSpeed() * timeInMilliseconds);
    obj.pitch(obj.getPitchRotationSpeed() * timeInMilliseconds);
    obj.yaw(obj.getYawRotationSpeed() * timeInMilliseconds);
}

void MoveableObjectPhysicsComponent::updatePosition(MoveableGameObject &obj, float time )
{
    obj.setPosition(obj.getPosition() + obj.getDirection() * obj.getSpeed() * time / 1000.0f);
}