#ifndef DOOMER_H
#define DOOMER_H

#include "../config.h"
#include "../include/Renderer.h"
#include <cmath>

class Doomer {
private:
  //resolution/scaling variables
  int resolution = 1;//0=160x120, 1=360x240, 2=640x480
  int scrnWidth = 160;
  int scrnHeight = 120;
  int scrnWidthHalf = scrnWidth/2;
  int scrnHeightHalf = scrnHeight/2;
  int pixelScale = 4/resolution;
  int SDL_win_w = (scrnWidth * pixelScale);
  int SDL_win_h = (scrnHeight* pixelScale);

  //array look up for pi conversion to degrees
  float cos[360];
  float sin[360];

  //Player postion variables
  int x, y, z; //z is up
  int a; //player angle of rotation
  int l; //look up or down

public:
  Doomer() {
    //create pi conversion lookup tables
    float pi = 3.14159265;
    for(int i=0;i<360;i++){
      this->cos[i] = std::cos(i/180*pi);
      this->sin[i] = std::sin(i/180*pi);
    }
  }

  // run once per game loop
  void RunFrame(Renderer* renderer);

  //movment functions
  void move_forward();
  void move_back();
  void move_right();
  void move_left();
  void move_strafe_right();
  void move_strafe_left();
  void move_look_up();
  void move_look_down();

};

#endif
