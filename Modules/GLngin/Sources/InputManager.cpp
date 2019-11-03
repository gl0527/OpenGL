#include "InputManager.hpp"
#include "Vec2.hpp"


namespace GLngin {

void OnKeyHelper (unsigned char key, bool state);
void OnMouseHelper (int x, int y);

namespace {

void OnKeyDown (unsigned char key, int /*x*/, int /*y*/)
{
    OnKeyHelper (key, true);
}


void OnKeyUp (unsigned char key, int /*x*/, int /*y*/)
{
    OnKeyHelper (key, false);
}


void OnSpecKeyDown (int key, int /*x*/, int /*y*/)
{
    OnKeyHelper (key + InputManager::specKeyOffset, true);
}


void OnSpecKeyUp (int key, int /*x*/, int /*y*/)
{
    OnKeyHelper (key + InputManager::specKeyOffset, false);
}


void OnMouseMotion (int x, int y)
{
    OnMouseHelper (x, y);
}


void OnMousePassiveMotion (int x, int y)
{
    OnMouseHelper (x, y);
}

}   // namespace


static auto& input = InputManager::Instance ();


void OnKeyHelper (unsigned char key, bool state)
{
    input.lastKey = key;
    input.keyState[input.lastKey].prevState = input.keyState[input.lastKey].state;
    input.keyState[input.lastKey].state = state;
    input.keyState[InputManager::Key::ANY].prevState = input.keyState[input.lastKey].prevState;
    input.keyState[InputManager::Key::ANY].state = input.keyState[input.lastKey].state;
}


void OnMouseHelper (int x, int y)
{
    input.dMouseX = x - input.mouseX;
    input.dMouseY = y - input.mouseY;
    input.mouseX = x;
    input.mouseY = y;
}


void OnMouse (int button, int state, int x, int y)
{
    if (button == InputManager::Mouse::SCROLL_UP ||
        button == InputManager::Mouse::SCROLL_DOWN)
    {
        input.mouseState[button] = input.SCROLL;
    } else {
        input.mouseState[button] = state;
    }
    OnMouseHelper (x, y);
}


InputManager::InputManager ():
    lastKey (-1),
    mouseX (-1),
    mouseY (-1),
    dMouseX (0),
    dMouseY (0),
    SCROLL (2)
{
    for (auto& s : keyState) {
        s = {false, false};
    }
    for (auto& s : mouseState) {
        s = -1;
    }
}


InputManager& InputManager::Instance ()
{
    static InputManager instance;
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


void InputManager::Disable ()
{
    UnBindCallbacks ();

    keyState[lastKey].state = false;
    mouseState[Mouse::LEFT_BUTTON] = GLUT_UP;
    mouseState[Mouse::MIDDLE_BUTTON] = GLUT_UP;
    mouseState[Mouse::RIGHT_BUTTON] = GLUT_UP;
    mouseState[Mouse::SCROLL_UP] = GLUT_UP;
    mouseState[Mouse::SCROLL_DOWN] = GLUT_UP;
}


bool InputManager::IsKeyPressed (Key key) const
{
    return keyState[key].state && !keyState[key].prevState;
}


bool InputManager::IsKeyDown (Key key) const
{
    return keyState[key].state;
}


bool InputManager::IsKeyReleased (Key key) const
{
    return !keyState[key].state && keyState[key].prevState;
}


Math::Vec2 InputManager::GetMouseCoordsInNDC () const
{
    const int wndWidth = glutGet (GLUT_WINDOW_WIDTH);
    const int wndHeight = glutGet (GLUT_WINDOW_HEIGHT);
    // Mouse coordinates in the normalized device coordinate system
    return {2.0f * mouseX / wndWidth - 1,
            2.0f * (wndHeight - mouseY) / wndHeight - 1};
}


Math::Vec2 InputManager::GetMouseCoordsInOpenGLWindowSpace () const
{
    // Mouse coordinates in a coordinate system where the origin is at the bottom left corner of the window
    return {mouseX, glutGet (GLUT_WINDOW_HEIGHT) - mouseY};
}


Math::Vec2 InputManager::GetMouseCoordsInGLUTWindowSpace () const
{
    // Mouse coordinates in a coordinate system where the origin is at the top left corner of the window
    return {mouseX, mouseY};
}


Math::Vec2 InputManager::GetMouseDelta () const
{
    return {dMouseX, -dMouseY}; // coordinate transform from GLUT to OpenGL
}


bool InputManager::IsLeftMouseButtonDown () const
{
    return mouseState[Mouse::LEFT_BUTTON] == GLUT_DOWN;
}


bool InputManager::IsRightMouseButtonDown () const
{
    return mouseState[Mouse::RIGHT_BUTTON] == GLUT_DOWN;
}


bool InputManager::IsMiddleMouseButtonDown () const
{
    return mouseState[Mouse::MIDDLE_BUTTON] == GLUT_DOWN;
}


bool InputManager::IsScrollUp () const
{
    return mouseState[Mouse::SCROLL_UP] == SCROLL;
}


bool InputManager::IsScrollDown () const
{
    return mouseState[Mouse::SCROLL_DOWN] == SCROLL;
}


void InputManager::Update ()
{
    keyState[lastKey].prevState = keyState[lastKey].state;

    mouseState[Mouse::SCROLL_UP] = GLUT_UP;
    mouseState[Mouse::SCROLL_DOWN] = GLUT_UP;

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
