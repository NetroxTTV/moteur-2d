#include "pch.h"
#include "Camera.h"

Camera::Camera(Entity* entity) : Component(entity)
{
}

Camera::~Camera() { }

int Camera::GetBitmask()
{
    return BITMASK;
}
