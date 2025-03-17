#include "pch.h"
#include "Camera.h"

Camera::Camera(Entity* entity, int display) : Component(entity), DisplayScreen(display) { }

int Camera::GetBitmask()
{
    return BITMASK;
}
