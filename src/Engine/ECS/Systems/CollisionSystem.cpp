#include "pch.h"
#include "CollisionSystem.h"

int MAX_ITERATIONS = 5;
float PENETRATION_SLACK = 0.25f;

CollisionSystem& CollisionSystem::Get()
{
    static CollisionSystem instance;    
    return instance;
}