// autotimer.cpp
#include "autotimer.h"
#include <iostream>
#if _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
class AutoTimer::Impl
{
public:
  double GetElapsed() const
  {
 #ifdef _WIN32
  return (GetTickCount() - mStartTime) / 1e3;
  #else
  struct timeval end_time;
  gettimeofday(&end_time, NULL);
  double t1 = mStartTime.tv_usec / 1e6 + mStartTime.tv_sec;
  double t2 = end_time.tv_usec / 1e6 + end_time.tv_sec;
  return t2 - t1;
 #endif
  }

  std::string mName;

#ifdef _WIN32
  DWORD mStartTime;
#else
struct timeval mStartTime;
#endif
};

AutoTimer::AutoTimer(const std::string &name) :
 mImpl(new AutoTimer::Impl())
{
 mImpl->mName = name;
#ifdef _WIN32
 mImpl->mStartTime = GetTickCount();
#else
 gettimeofday(&mImpl->mStartTime, NULL);
#endif
}

AutoTimer::~AutoTimer()
{
 std::cout << mImpl->mName << ": took " << mImpl->GetElapsed()
	<< " secs" << std::endl;
 delete mImpl;
 mImpl = NULL;
}
