#include "../include/Timer.h"

void Timer::start_timer(){
      this->start_time = SDL_GetPerformanceCounter();
    }

Uint64 Timer::stop_timer(){
  if(start_time != 0){
    this->end_time = SDL_GetPerformanceCounter();
    this->ellapsed_time = (end_time - start_time) / (float)SDL_GetPerformanceFrequency();
    return ellapsed_time;
  }else{
    std::cout << "Error: Timer was never started.." << std::endl;
    return 0;
  }
}
