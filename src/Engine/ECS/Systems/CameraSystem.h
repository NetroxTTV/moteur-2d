#pragma once

class RenderWindow;
class ECS;

class CameraSystem
{
    
public:
    CameraSystem(RenderWindow* window);
    ~CameraSystem() = default;

    void SetActiveCamera(int activeCamera);
    TRANSFORM* GetActiveCamera();
    
    void Update(ECS* globalEC);

private:
    int mCurrentDisplayedCamera;
    TRANSFORM* mTransformCamera;
    RenderWindow* mWindow;
};
