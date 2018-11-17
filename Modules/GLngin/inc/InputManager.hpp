#pragma once

#ifndef GLNGIN_INPUT_MANAGER_HPP
#define GLNGIN_INPUT_MANAGER_HPP

#include "API.hpp"

#include <GL/freeglut_std.h>


namespace GLngin {

class GLNGIN_API InputManager final {
public:
    static constexpr unsigned char specKeyOffset = 128;

    enum class KeyCode {
        KC_BACKSPACE    = 8,
        KC_TAB          = '\t',
        KC_ENTER        = '\r',
        KC_ESCAPE       = 27,
        KC_SPACE        = ' ',
        KC_ASTERISK     = '*',
        KC_PLUS         = '+',
        KC_MINUS        = '-',

        KC_0            = '0',
        KC_1            = '1',
        KC_2            = '2',
        KC_3            = '3',
        KC_4            = '4',
        KC_5            = '5',
        KC_6            = '6',
        KC_7            = '7',
        KC_8            = '8',
        KC_9            = '9',

        KC_A            = 'A',
        KC_B            = 'B',
        KC_C            = 'C',
        KC_D            = 'D',
        KC_E            = 'E',
        KC_F            = 'F',
        KC_G            = 'G',
        KC_H            = 'H',
        KC_I            = 'I',
        KC_J            = 'J',
        KC_K            = 'K',
        KC_L            = 'L',
        KC_M            = 'M',
        KC_N            = 'N',
        KC_O            = 'O',
        KC_P            = 'P',
        KC_Q            = 'Q',
        KC_R            = 'R',
        KC_S            = 'S',
        KC_T            = 'T',
        KC_U            = 'U',
        KC_V            = 'V',
        KC_W            = 'W',
        KC_X            = 'X',
        KC_Y            = 'Y',
        KC_Z            = 'Z',

        KC_a            = 'a',
        KC_b            = 'b',
        KC_c            = 'c',
        KC_d            = 'd',
        KC_e            = 'e',
        KC_f            = 'f',
        KC_g            = 'g',
        KC_h            = 'h',
        KC_i            = 'i',
        KC_j            = 'j',
        KC_k            = 'k',
        KC_l            = 'l',
        KC_m            = 'm',
        KC_n            = 'n',
        KC_o            = 'o',
        KC_p            = 'p',
        KC_q            = 'q',
        KC_r            = 'r',
        KC_s            = 's',
        KC_t            = 't',
        KC_u            = 'u',
        KC_v            = 'v',
        KC_w            = 'w',
        KC_x            = 'x',
        KC_y            = 'y',
        KC_z            = 'z',

        KC_DELETE       = 127,

        KC_F1           = GLUT_KEY_F1 + specKeyOffset,
        KC_F2           = GLUT_KEY_F2 + specKeyOffset,
        KC_F3           = GLUT_KEY_F3 + specKeyOffset,
        KC_F4           = GLUT_KEY_F4 + specKeyOffset,
        KC_F5           = GLUT_KEY_F5 + specKeyOffset,
        KC_F6           = GLUT_KEY_F6 + specKeyOffset,
        KC_F7           = GLUT_KEY_F7 + specKeyOffset,
        KC_F8           = GLUT_KEY_F8 + specKeyOffset,
        KC_F9           = GLUT_KEY_F9 + specKeyOffset,
        KC_F10          = GLUT_KEY_F10 + specKeyOffset,
        KC_F11          = GLUT_KEY_F11 + specKeyOffset,
        KC_F12          = GLUT_KEY_F12 + specKeyOffset,
        KC_LEFT         = GLUT_KEY_LEFT + specKeyOffset,
        KC_UP           = GLUT_KEY_UP + specKeyOffset,
        KC_RIGHT        = GLUT_KEY_RIGHT + specKeyOffset,
        KC_DOWN         = GLUT_KEY_DOWN + specKeyOffset,
        KC_PGUP         = GLUT_KEY_PAGE_UP + specKeyOffset,
        KC_PGDOWN       = GLUT_KEY_PAGE_DOWN + specKeyOffset,
        KC_HOME         = GLUT_KEY_HOME + specKeyOffset,
        KC_END          = GLUT_KEY_END + specKeyOffset,
        KC_INSERT       = GLUT_KEY_INSERT + specKeyOffset,
    };

    static InputManager&    Instance ();

                            InputManager (const InputManager&) = delete;
    InputManager&           operator= (const InputManager&) = delete;

    void                    Init ();

    void                    Enable ();
    void                    Disable ();

    bool                    IsKeyPressed (KeyCode key);
    bool                    IsKeyDown (KeyCode key);
    bool                    IsKeyReleased (KeyCode key);

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
