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

    bool                    IsKeyPressed (unsigned char key);
    bool                    IsKeyDown (unsigned char key);
    bool                    IsKeyReleased (unsigned char key);

    bool                    IsSpecKeyPressed (int key);
    bool                    IsSpecKeyDown (int key);
    bool                    IsSpecKeyReleased (int key);

    void                    GetMousePosition (int * x, int * y);
    bool                    IsLeftMouseButtonDown ();
    bool                    IsRightMouseButtonDown ();
    bool                    IsMiddleMouseButtonDown ();

    void                    Update ();

private:
    static InputManager instance;

                            InputManager ();
};

}   // namespace GLngin

#endif  // #ifndef GLNGIN_INPUT_MANAGER_HPP
