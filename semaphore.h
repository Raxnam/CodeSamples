/**********************************************************
 * Cameron Monks
 * CS 255
 * Assignment 2: Semaphore
 * semaphore.h
***********************************************************/
#include <mutex>
#include <condition_variable>
class Semaphore
{
public:
	Semaphore();
	Semaphore(int c);
	inline void wait()
{
  std::unique_lock<std::mutex> lock(mutex);
  while(!count)
  {
    block.wait(lock);
  }
  count--;
}

inline void  signal()
{
  std::unique_lock<std::mutex> lock(mutex);
  count++;
  block.notify_one();
}
private:
	int count;
	std::mutex mutex;
	std::condition_variable block;
};
