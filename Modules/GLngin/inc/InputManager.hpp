#pragma once

#ifndef GLNGIN_INPUT_MANAGER_HPP
#define GLNGIN_INPUT_MANAGER_HPP

#include "API.hpp"


namespace GLngin {

class GLNGIN_API InputManager final {
public:
    static InputManager&    Instance ();

                            InputManager (const InputManager&) = delete;
    InputManager&           operator= (const InputManager&) = delete;

    void                    Init ();

    void                    Enable ();
    void                    Disable ();

    bool                    IsKeyPressed (unsigned char key);
    bool                    IsKeyDown (unsigned char key);
    bool                    IsKeyReleased (unsigned char key);

    bool                    IsSpecKeyPressed (int key);
    bool                    IsSpecKeyDown (int key);
    bool                    IsSpecKeyReleased (int key);

    void                    GetMouseCoordsInNDC (float * x, float * y);
    void                    GetMouseCoordsInOpenGLWindowSpace (int * x, int * y);
    void                    GetMouseCoordsInGLUTWindowSpace (int * x, int * y);

    bool                    IsLeftMouseButtonDown ();
    bool                    IsRightMouseButtonDown ();
    bool                    IsMiddleMouseButtonDown ();

    void                    Update ();

private:
    static InputManager instance;

                            InputManager ();

    void                    BindCallbacks ();
    void                    UnBindCallbacks ();
};

}   // namespace GLngin

#endif  // #ifndef GLNGIN_INPUT_MANAGER_HPP
