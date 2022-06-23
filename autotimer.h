// autotimer.h
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#include <string>
class AutoTimer
{
public:
/// Create a new timer object with a human-readable name
explicit AutoTimer(const std::string &name);
/// On destruction, the timer reports how long it was alive
AutoTimer();
private:
// Return how long the object has been alive
double GetElapsed() const;
std::string mName;
#ifdef _WIN32
DWORD mStartTime;
#else
struct timeval mStartTime;
#endif
};
