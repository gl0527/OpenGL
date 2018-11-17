#include "InputManager.hpp"

#include <GL/freeglut.h>


namespace GLngin {

namespace {

struct KeyData {
    bool isDown;
    bool isPressed;
    bool isReleased;
};


KeyData keyState[256] = { {false, false, false} };
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
    lastKey = key + InputManager::specKeyOffset;
    keyState[lastKey].isPressed = true;
    keyState[lastKey].isDown = true;
}


void OnSpecKeyUp (int key, int /*x*/, int /*y*/)
{
    lastKey = key + InputManager::specKeyOffset;
    keyState[lastKey].isReleased = true;
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


void OnMousePassiveMotion (int x, int y)
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
    BindCallbacks ();
}


void InputManager::Enable ()
{
    BindCallbacks ();
}


void InputManager::Disable ()
{
    UnBindCallbacks ();

    keyState[lastKey].isDown = false;
    mouseState[GLUT_LEFT_BUTTON] = GLUT_UP;
    mouseState[GLUT_MIDDLE_BUTTON] = GLUT_UP;
    mouseState[GLUT_RIGHT_BUTTON] = GLUT_UP;
}


bool InputManager::IsKeyPressed (KeyCode key)
{
    return keyState[static_cast<unsigned char> (key)].isPressed;
}


bool InputManager::IsKeyDown (KeyCode key)
{
    return keyState[static_cast<unsigned char> (key)].isDown;
}


bool InputManager::IsKeyReleased (KeyCode key)
{
    return keyState[static_cast<unsigned char> (key)].isReleased;
}


void InputManager::GetMouseCoordsInNDC (float * x, float * y)
{
    // Mouse coordinates in the normalized device coordinate system
    *x = 2.0f * mouseX / glutGet (GLUT_WINDOW_WIDTH) - 1;
    *y = 2.0f * (glutGet (GLUT_WINDOW_HEIGHT) - mouseY) / glutGet (GLUT_WINDOW_HEIGHT) - 1;
}


void InputManager::GetMouseCoordsInOpenGLWindowSpace (int * x, int * y)
{
    // Mouse coordinates in a coordinate system where the origin is at the bottom left corner of the window
    *x = mouseX;
    *y = glutGet (GLUT_WINDOW_HEIGHT) - mouseY;
}


void InputManager::GetMouseCoordsInGLUTWindowSpace (int * x, int * y)
{
    // Mouse coordinates in a coordinate system where the origin is at the top left corner of the window
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


void InputManager::BindCallbacks ()
{
    // keyboard-related callbacks
    glutKeyboardFunc (OnKeyDown);
    glutKeyboardUpFunc (OnKeyUp);
    glutSpecialFunc (OnSpecKeyDown);
    glutSpecialUpFunc (OnSpecKeyUp);

    // mouse-related callbacks
    glutMouseFunc (OnMouse);
    glutMotionFunc (OnMouseMotion);
    glutPassiveMotionFunc (OnMousePassiveMotion);
}


void InputManager::UnBindCallbacks ()
{
    // keyboard-related callbacks
    glutKeyboardFunc (nullptr);
    glutKeyboardUpFunc (nullptr);
    glutSpecialFunc (nullptr);
    glutSpecialUpFunc (nullptr);

    // mouse-related callbacks
    glutMouseFunc (nullptr);
    glutMotionFunc (nullptr);
    glutPassiveMotionFunc (nullptr);
}

}   // namespace GLngin
