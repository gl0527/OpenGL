#include "InputManager.hpp"

#include <GL/freeglut.h>


namespace GLngin {

namespace {

struct KeyData {
    bool isDown;
    bool isPressed;
    bool isReleased;
};


KeyData keyState[512] = { {false, false, false} };
int mouseState[3] = { -1, -1, -1 };
int lastKey = -1;
int mouseX = -1;
int mouseY = -1;


void OnKeyDown (unsigned char key, int /*x*/, int /*y*/)
{
    lastKey = key;
    keyState[lastKey].isPressed = true;
    keyState[lastKey].isDown = true;
}


void OnKeyUp (unsigned char key, int /*x*/, int /*y*/)
{
    lastKey = key;
    keyState[lastKey].isReleased = true;
    keyState[lastKey].isDown = false;
}


void OnSpecKeyDown (int key, int /*x*/, int /*y*/)
{
    lastKey = key + 256;
    keyState[lastKey].isPressed = true;
    keyState[lastKey].isDown = true;
}


void OnSpecKeyUp (int key, int /*x*/, int /*y*/)
{
    lastKey = key + 256;
    keyState[lastKey].isPressed = true;
    keyState[lastKey].isDown = false;
}


void OnMouse (int button, int state, int x, int y)
{
    mouseState[button] = state;
    mouseX = x;
    mouseY = y;
}


void OnMouseMotion (int x, int y)
{
    mouseX = x;
    mouseY = y;
}

}   // namespace


InputManager InputManager::instance;


InputManager& InputManager::Instance ()
{
    return instance;
}


void InputManager::Init ()
{
    glutKeyboardFunc (OnKeyDown);
    glutKeyboardUpFunc (OnKeyUp);
    glutSpecialFunc (OnSpecKeyDown);
    glutSpecialUpFunc (OnSpecKeyUp);
    glutMouseFunc (OnMouse);
    glutMotionFunc (OnMouseMotion);
}


bool InputManager::IsKeyPressed (unsigned char key)
{
    return keyState[key].isPressed;
}


bool InputManager::IsKeyDown (unsigned char key)
{
    return keyState[key].isDown;
}


bool InputManager::IsKeyReleased (unsigned char key)
{
    return keyState[key].isReleased;
}


bool InputManager::IsSpecKeyPressed (int key)
{
    return keyState[key + 256].isPressed;
}


bool InputManager::IsSpecKeyDown (int key)
{
    return keyState[key + 256].isDown;
}


bool InputManager::IsSpecKeyReleased (int key)
{
    return keyState[key + 256].isReleased;
}


void InputManager::GetMousePosition (int * x, int * y)
{
    *x = mouseX;
    *y = mouseY;
}


bool InputManager::IsLeftMouseButtonDown ()
{
    return mouseState[GLUT_LEFT_BUTTON] == GLUT_DOWN;
}


bool InputManager::IsRightMouseButtonDown ()
{
    return mouseState[GLUT_RIGHT_BUTTON] == GLUT_DOWN;
}


bool InputManager::IsMiddleMouseButtonDown ()
{
    return mouseState[GLUT_MIDDLE_BUTTON] == GLUT_DOWN;
}


void InputManager::Update ()
{
    keyState[lastKey].isPressed = false;
    keyState[lastKey].isReleased = false;
}


InputManager::InputManager ()
{
}

}   // namespace GLngin
