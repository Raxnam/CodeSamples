/**********************************************************
 * Cameron Monks
 * CS 255
 * Assignment 2: Semaphore
 * semaphore.h
***********************************************************/
#include <mutex>
#include <condition_variable>

//Semaphore class
class Semaphore
{
  public:
    Semaphore();
    Semaphore(int c);

    //inline function for the wait
    //decrements counter and blocks if the counter is negative
    inline void wait()
    {
      std::unique_lock<std::mutex> lock(mutex);
      while (!count)
      {
        block.wait(lock);
      }
      count--;
    }

    //inline function for singal
    //increments the counter and wakes a waiting thread if the counter is greater than or equal to zero
    inline void  signal()
    {
      std::unique_lock<std::mutex> lock(mutex);
      count++;
      block.notify_one();
    }

  private:
    //counter variable
    int count;
    //mutex in charge of locking
    std::mutex mutex;
    //conditional variable in charge of blocking threads
    std::condition_variable block;
};
