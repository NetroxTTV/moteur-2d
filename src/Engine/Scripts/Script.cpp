#include "pch.h"
#include "Script.h"

IScript::IScript(): owner(nullptr)
{
}

void IScript::OnStart()
{
}

void IScript::OnUpdate()
{
}

void IScript::OnFixedUpdate()
{
}

void IScript::OnCollisionEnter(Entity* other)
{
}

void IScript::OnCollisionStay(Entity* other)
{
}

void IScript::OnCollisionExit(Entity* other)
{
}

void IScript::OnTriggerEnter(Entity* other)
{
}

void IScript::OnTriggerStay(Entity* other)
{
}

void IScript::OnTriggerExit(Entity* other)
{
}

void IScript::OnRender(RenderWindow* window)
{
}

void IScript::OnRenderDisable()
{
}

void IScript::OnDisable()
{
}

void IScript::SetOwner(Entity* entity)
{
    owner = entity;
}
