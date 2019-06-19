#include "Timer.hpp"

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <sys/time.h>
#endif


#ifdef __linux__
namespace {

unsigned int timeGetTime ()
{
    static struct timeval start;
    static bool first = true;
    if (first) {
        gettimeofday (&start, nullptr);
        first = false;
    }
    struct timeval now;
    gettimeofday (&now, nullptr);
    return now.tv_usec / 1000 + (now.tv_sec - start.tv_sec) * 1000;
}

}
#endif


namespace GLngin {

Timer::Timer () :
    m_prevTime (0.0f),
    upTime (0.0f),
    m_deltaTime (0.0f),
    m_isRunning (true)
{
}


void Timer::Tick ()
{
    if (!m_isRunning)
        return;

    float currTime = timeGetTime () * 1e-3f;

    if (m_prevTime < 1e-4f)
        m_prevTime = currTime;

    m_deltaTime = currTime - m_prevTime;
    upTime += m_deltaTime;
    m_prevTime = currTime;
}


void Timer::Reset ()
{
    m_prevTime = 0.0f;
    upTime = 0.0f;
    m_deltaTime = 0.0f;
}


void Timer::Pause ()
{
    Reset ();
    m_isRunning = false;
}


void Timer::Resume ()
{
    m_isRunning = true;
}


float Timer::GetUptime () const
{
    return upTime;
}


float Timer::GetDeltaTime () const
{
    return m_deltaTime;
}

}   // namespace GLngin
