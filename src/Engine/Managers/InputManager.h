#pragma once

#include <array>
#include <windows.h>

class InputManager {
public:
    InputManager();
    void Update();

    bool IsKeyPressed(int keycode) const;
    bool IsKeyJustPressed(int keycode) const;
    bool IsKeyJustReleased(int keycode) const;
    bool IsMouseButtonPressed(int button) const;
    bool IsMouseButtonJustPressed(int button) const;

    void GetMousePosition(int& x, int& y) const;
    int GetMouseDeltaX() const { return mMouseDeltaX; }
    int GetMouseDeltaY() const { return mMouseDeltaY; }

private:
    std::array<bool, 256> mCurrentKeyStates;
    std::array<bool, 256> mPreviousKeyStates;

    std::array<bool, 5> mCurrentMouseStates;
    std::array<bool, 5> mPreviousMouseStates;


    int mMouseDeltaX; 
    int mMouseDeltaY;
    POINT mMousePosition;
};