#include "pch.h"
#include "InputManager.h"

#include "Keycode.h"

InputManager::InputManager() 
{
    for (int i = 0; i < 256; ++i) {
        mCurrentKeyStates[i] = false;
        mPreviousKeyStates[i] = false;
    }

    for (int i = 0; i < 5; ++i) {
        mCurrentMouseStates[i] = false;
        mPreviousMouseStates[i] = false;
    }

    mMouseDeltaX = 0;
    mMouseDeltaY = 0;

    GetCursorPos(&mMousePosition);
}

void InputManager::Update() 
{
    POINT newMousePosition;
    GetCursorPos(&newMousePosition);

    mMouseDeltaX = newMousePosition.x - mMousePosition.x;
    mMouseDeltaY = newMousePosition.y - mMousePosition.y;

    mMousePosition = newMousePosition;

    mPreviousKeyStates = mCurrentKeyStates;
    for (int i = 0; i < 256; ++i) {
        mCurrentKeyStates[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
    }
    GetCursorPos(&mMousePosition);

    mCurrentMouseStates[0] = (GetAsyncKeyState(MOUSE_LEFT) & 0x8000) != 0;
    mCurrentMouseStates[1] = (GetAsyncKeyState(MOUSE_RIGHT) & 0x8000) != 0;
    mCurrentMouseStates[2] = (GetAsyncKeyState(MOUSE_MIDDLE) & 0x8000) != 0;
    mCurrentMouseStates[3] = (GetAsyncKeyState(MOUSE_XBUTTON1) & 0x8000) != 0;
    mCurrentMouseStates[4] = (GetAsyncKeyState(MOUSE_XBUTTON2) & 0x8000) != 0;
}

bool InputManager::IsKeyPressed(int keycode) const 
{
    return mCurrentKeyStates.at(keycode);
}

bool InputManager::IsKeyJustPressed(int keycode) const 
{
    return mCurrentKeyStates.at(keycode) && !mPreviousKeyStates.at(keycode);
}

bool InputManager::IsKeyJustReleased(int keycode) const 
{
    return !mCurrentKeyStates.at(keycode) && mPreviousKeyStates.at(keycode);
}

bool InputManager::IsMouseButtonPressed(int button) const
{
    return mCurrentMouseStates.at(button);
}

bool InputManager::IsMouseButtonJustPressed(int button) const
{
    return mCurrentMouseStates.at(button) && !mPreviousMouseStates.at(button);
}

void InputManager::GetMousePosition(int& x, int& y) const 
{
    x = mMousePosition.x;
    y = mMousePosition.y;
}