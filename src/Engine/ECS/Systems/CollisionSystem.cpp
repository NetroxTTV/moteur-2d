#include "pch.h"
#include "CollisionSystem.h"

#include "ECS/ECS.h"
#include "ECS/Components/PhysicsMaterial.h"
#include "ECS/Components/RigidBody2D.h"
#include "scripts/ScriptManager.h"
#include "Utils/Profiler.h"

int MAX_ITERATIONS = 5;
float PENETRATION_SLACK = 0.25f;

CollisionSystem& CollisionSystem::Get()
{
    static CollisionSystem instance;    
    return instance;
}