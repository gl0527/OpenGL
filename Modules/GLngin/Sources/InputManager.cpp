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
unsigned char anyKey = static_cast<unsigned char> (InputManager::Key::ANY);

int mouseX = -1;
int mouseY = -1;
int dMouseX = 0;
int dMouseY = 0;


void OnKeyDown (unsigned char key, int /*x*/, int /*y*/)
{
    lastKey = key;
    keyState[lastKey].isPressed = true;
    keyState[lastKey].isDown = true;

    keyState[anyKey].isPressed = true;
    keyState[anyKey].isDown = true;
}


void OnKeyUp (unsigned char key, int /*x*/, int /*y*/)
{
    lastKey = key;
    keyState[lastKey].isReleased = true;
    keyState[lastKey].isDown = false;

    keyState[anyKey].isReleased = true;
    keyState[anyKey].isDown = false;
}


void OnSpecKeyDown (int key, int /*x*/, int /*y*/)
{
    lastKey = key + InputManager::specKeyOffset;
    keyState[lastKey].isPressed = true;
    keyState[lastKey].isDown = true;

    keyState[anyKey].isPressed = true;
    keyState[anyKey].isDown = true;
}


void OnSpecKeyUp (int key, int /*x*/, int /*y*/)
{
    lastKey = key + InputManager::specKeyOffset;
    keyState[lastKey].isReleased = true;
    keyState[lastKey].isDown = false;

    keyState[anyKey].isReleased = true;
    keyState[anyKey].isDown = false;
}


void OnMouse (int button, int state, int x, int y)
{
    mouseState[button] = state;
    dMouseX = mouseX > 0 ? x - mouseX : 0;
    dMouseY = mouseY > 0 ? y - mouseY : 0;
    mouseX = x;
    mouseY = y;
}


void OnMouseMotion (int x, int y)
{
    dMouseX = mouseX > 0 ? x - mouseX : 0;
    dMouseY = mouseY > 0 ? y - mouseY : 0;
    mouseX = x;
    mouseY = y;
}


void OnMousePassiveMotion (int x, int y)
{
    dMouseX = mouseX > 0 ? x - mouseX : 0;
    dMouseY = mouseY > 0 ? y - mouseY : 0;
    mouseX = x;
    mouseY = y;
}

}   // namespace


InputManager InputManager::instance;


InputManager& InputManager::Instance ()
{
    return instance;
}


void InputManager::Init () const
{
    BindCallbacks ();
}


void InputManager::Enable () const
{
    BindCallbacks ();
}


void InputManager::Disable () const
{
    UnBindCallbacks ();

    keyState[lastKey].isDown = false;
    mouseState[GLUT_LEFT_BUTTON] = GLUT_UP;
    mouseState[GLUT_MIDDLE_BUTTON] = GLUT_UP;
    mouseState[GLUT_RIGHT_BUTTON] = GLUT_UP;
}


bool InputManager::IsKeyPressed (Key key) const
{
    return keyState[static_cast<unsigned char> (key)].isPressed;
}


bool InputManager::IsKeyDown (Key key) const
{
    return keyState[static_cast<unsigned char> (key)].isDown;
}


bool InputManager::IsKeyReleased (Key key) const
{
    return keyState[static_cast<unsigned char> (key)].isReleased;
}


void InputManager::GetMouseCoordsInNDC (float * x, float * y) const
{
    // Mouse coordinates in the normalized device coordinate system
    *x = 2.0f * mouseX / glutGet (GLUT_WINDOW_WIDTH) - 1;
    *y = 2.0f * (glutGet (GLUT_WINDOW_HEIGHT) - mouseY) / glutGet (GLUT_WINDOW_HEIGHT) - 1;
}


void InputManager::GetMouseCoordsInOpenGLWindowSpace (int * x, int * y) const
{
    // Mouse coordinates in a coordinate system where the origin is at the bottom left corner of the window
    *x = mouseX;
    *y = glutGet (GLUT_WINDOW_HEIGHT) - mouseY;
}


void InputManager::GetMouseCoordsInGLUTWindowSpace (int * x, int * y) const
{
    // Mouse coordinates in a coordinate system where the origin is at the top left corner of the window
    *x = mouseX;
    *y = mouseY;
}


void InputManager::GetMouseDelta (int * dx, int * dy) const
{
    *dx = dMouseX;
    *dy = -dMouseY; // coordinate transform from GLUT to OpenGL
}


bool InputManager::IsLeftMouseButtonDown () const
{
    return mouseState[GLUT_LEFT_BUTTON] == GLUT_DOWN;
}


bool InputManager::IsRightMouseButtonDown () const
{
    return mouseState[GLUT_RIGHT_BUTTON] == GLUT_DOWN;
}


bool InputManager::IsMiddleMouseButtonDown () const
{
    return mouseState[GLUT_MIDDLE_BUTTON] == GLUT_DOWN;
}


void InputManager::Update () const
{
    keyState[lastKey].isPressed = false;
    keyState[lastKey].isReleased = false;

    dMouseX = 0;
    dMouseY = 0;
}


void InputManager::BindCallbacks () const
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


void InputManager::UnBindCallbacks () const
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
