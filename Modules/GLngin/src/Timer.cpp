#include "Timer.hpp"
#include <GL/freeglut.h>


namespace GLngin {

Timer::Timer () :
    m_prevTime (0.0f),
    m_upTime (0.0f),
    m_deltaTime (0.0f)
{
}


void Timer::Tick ()
{
    m_upTime = glutGet (GLUT_ELAPSED_TIME) * 1e-3f;

    if (m_prevTime < 1.0e-4f)
        m_prevTime = m_upTime;

    m_deltaTime = m_upTime - m_prevTime;
    m_prevTime = m_upTime;
}


void Timer::Reset ()
{
    m_prevTime = 0.0f;
    m_upTime = 0.0f;
    m_deltaTime = 0.0f;
}


void Timer::Pause ()
{
    m_prevTime = glutGet (GLUT_ELAPSED_TIME) * 1e-3f;
}


float Timer::GetUptime () const
{
    return m_upTime;
}


float Timer::GetDeltaTime () const
{
    return m_deltaTime;
}

}   // namespace GLngin
