#pragma once

#ifndef GLNGIN_TIMER_HPP
#define GLNGIN_TIMER_HPP

#include "API.hpp"


namespace GLngin {

class GLNGIN_API Timer {
public:
            Timer ();

    void    Tick ();
    void    Reset ();
    void    Pause ();
    void    Resume ();

    float   GetUptime () const;
    float   GetDeltaTime () const;

private:
    float   m_prevTime;
    float   upTime;
    float   m_deltaTime;
    bool    m_isRunning;
};

}   // namespace GLngin

#endif  // #ifndef GLNGIN_TIMER_HPP
