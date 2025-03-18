#pragma once
#include "ECS/Entity.h"

struct IScript
{
    
    IScript();
    virtual ~IScript() = default;
    
    virtual void OnStart();
    
    virtual void OnUpdate();
    virtual void OnFixedUpdate();

    virtual void OnCollisionEnter(Entity* other);
    virtual void OnCollisionStay(Entity* other);
    virtual void OnCollisionExit(Entity* other);

    virtual void OnTriggerEnter(Entity* other);
    virtual void OnTriggerStay(Entity* other);
    virtual void OnTriggerExit(Entity* other);

    virtual void OnRender(RenderWindow* window);
    
    virtual void OnRenderDisable();
    virtual void OnDisable();

protected:
    Entity* owner;

private:
    void SetOwner(Entity* entity);
    
    friend ScriptManager;
};
