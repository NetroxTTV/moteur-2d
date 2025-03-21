#pragma once

class Camera;
class RenderWindow;
class ECS;

class CameraSystem
{
    
public:
    CameraSystem(RenderWindow* window);
    ~CameraSystem() = default;

    void SetActiveCamera(int activeCamera);
    Camera* GetActiveCamera();
    
    void Update(ECS* globalEC);

private:
    int mCurrentDisplayedCamera;
    Camera* mCurrentCamera;
    RenderWindow* mWindow;
};
