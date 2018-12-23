#pragma once

#ifndef GLNGIN_INPUT_MANAGER_HPP
#define GLNGIN_INPUT_MANAGER_HPP

#include "API.hpp"

#include <GL/freeglut_std.h>


namespace GLngin {

class GLNGIN_API InputManager final {
public:
    static constexpr unsigned char specKeyOffset = 128;

    enum class Key : unsigned char {
        ANY          = 0,

        BACKSPACE    = 8,
        TAB          = '\t',
        ENTER        = '\r',
        ESCAPE       = 27,
        SPACE        = ' ',
        ASTERISK     = '*',
        PLUS         = '+',
        MINUS        = '-',

        ZERO         = '0',
        ONE          = '1',
        TWO          = '2',
        THREE        = '3',
        FOUR         = '4',
        FIVE         = '5',
        SIX          = '6',
        SEVEN        = '7',
        EIGHT        = '8',
        NINE         = '9',

        A            = 'A',
        B            = 'B',
        C            = 'C',
        D            = 'D',
        E            = 'E',
        F            = 'F',
        G            = 'G',
        H            = 'H',
        I            = 'I',
        J            = 'J',
        K            = 'K',
        L            = 'L',
        M            = 'M',
        N            = 'N',
        O            = 'O',
        P            = 'P',
        Q            = 'Q',
        R            = 'R',
        S            = 'S',
        T            = 'T',
        U            = 'U',
        V            = 'V',
        W            = 'W',
        X            = 'X',
        Y            = 'Y',
        Z            = 'Z',

        a            = 'a',
        b            = 'b',
        c            = 'c',
        d            = 'd',
        e            = 'e',
        f            = 'f',
        g            = 'g',
        h            = 'h',
        i            = 'i',
        j            = 'j',
        k            = 'k',
        l            = 'l',
        m            = 'm',
        n            = 'n',
        o            = 'o',
        p            = 'p',
        q            = 'q',
        r            = 'r',
        s            = 's',
        t            = 't',
        u            = 'u',
        v            = 'v',
        w            = 'w',
        x            = 'x',
        y            = 'y',
        z            = 'z',

        DELETE       = 127,

        F1           = GLUT_KEY_F1 + specKeyOffset,
        F2           = GLUT_KEY_F2 + specKeyOffset,
        F3           = GLUT_KEY_F3 + specKeyOffset,
        F4           = GLUT_KEY_F4 + specKeyOffset,
        F5           = GLUT_KEY_F5 + specKeyOffset,
        F6           = GLUT_KEY_F6 + specKeyOffset,
        F7           = GLUT_KEY_F7 + specKeyOffset,
        F8           = GLUT_KEY_F8 + specKeyOffset,
        F9           = GLUT_KEY_F9 + specKeyOffset,
        F10          = GLUT_KEY_F10 + specKeyOffset,
        F11          = GLUT_KEY_F11 + specKeyOffset,
        F12          = GLUT_KEY_F12 + specKeyOffset,
        LEFT         = GLUT_KEY_LEFT + specKeyOffset,
        UP           = GLUT_KEY_UP + specKeyOffset,
        RIGHT        = GLUT_KEY_RIGHT + specKeyOffset,
        DOWN         = GLUT_KEY_DOWN + specKeyOffset,
        PGUP         = GLUT_KEY_PAGE_UP + specKeyOffset,
        PGDOWN       = GLUT_KEY_PAGE_DOWN + specKeyOffset,
        HOME         = GLUT_KEY_HOME + specKeyOffset,
        END          = GLUT_KEY_END + specKeyOffset,
        INSERT       = GLUT_KEY_INSERT + specKeyOffset,
    };

    static InputManager&    Instance ();

                            InputManager (const InputManager&) = delete;
    InputManager&           operator= (const InputManager&) = delete;

    void                    Init () const;

    void                    Enable () const;
    void                    Disable () const;

    bool                    IsKeyPressed (Key key) const;
    bool                    IsKeyDown (Key key) const;
    bool                    IsKeyReleased (Key key) const;

    void                    GetMouseCoordsInNDC (float * x, float * y) const;
    void                    GetMouseCoordsInOpenGLWindowSpace (int * x, int * y) const;
    void                    GetMouseCoordsInGLUTWindowSpace (int * x, int * y) const;

    void                    GetMouseDelta (int * dx, int * dy) const;

    bool                    IsLeftMouseButtonDown () const;
    bool                    IsRightMouseButtonDown () const;
    bool                    IsMiddleMouseButtonDown () const;

    void                    Update () const;

private:
    static InputManager instance;

                            InputManager () = default;

    void                    BindCallbacks () const;
    void                    UnBindCallbacks () const;
};

}   // namespace GLngin

#endif  // #ifndef GLNGIN_INPUT_MANAGER_HPP
