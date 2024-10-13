#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "../config.h"
#include "../include/Renderer.h"

class Raycaster {
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

  // calculation variables
  double posX = 22, posY = 12;      // x and y start postion
  double dirX = -1, dirY = 0;       // initial direction vector
  double planeX = 0, planeY = 0.66; // the 2d raycaster version of camera plane

  // time variables for tracking frames
  double time = 0;    // time of current frame
  double oldTime = 0; // time of previous frame

  //movement variables
  double moveSpeed = .05 * 5.0; //the constant value is in squares/second
  double rotSpeed = .05 * 3.0; //the constant value is in radians/second  

public:
  Raycaster(int scrnWidth, int scrnHeight) {
    this->scrnWidth = scrnWidth;
    this->scrnHeight = scrnHeight;
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
