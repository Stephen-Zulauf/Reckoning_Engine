#ifndef TIMER_H
#define TIMER_H

#include "../config.h"
#include <SDL2/SDL_timer.h>

//SDL dependent timer class

class Timer{
  private:
    Uint64 start_time = 0;
    Uint64 end_time;
    float ellapsed_time;

  public:
    void start_timer();
    Uint64 stop_timer();    
};





#endif
