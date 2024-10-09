#include "../include/Raycaster.h"

// run once per game loop
void Raycaster::RunFrame(Renderer *renderer) {
  for (int x = 0; x < scrnWidth; x++) {

    // calculate ray position and direction
    double cameraX =
        2 * x / (double)scrnWidth - 1; // x-coordinate in camera space
    double rayDirX = dirX + planeX * cameraX;
    double rayDirY = dirY + planeY * cameraX;

    // which box of the map we're in
    int mapX = int(posX);
    int mapY = int(posY);

    // length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;

    // length of ray from one x or y-side to next x or y-side
    double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
    double perpWallDist;

    // what direction to step in x or y-direction (either +1 or -1)
    int stepX;
    int stepY;

    int hit = 0; // was there a wall hit?
    int side;    // was a NS or a EW wall hit?

    // calculate step and initial sideDist
    if (rayDirX < 0) {
      stepX = -1;
      sideDistX = (posX - mapX) * deltaDistX;
    } else {
      stepX = 1;
      sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0) {
      stepY = -1;
      sideDistY = (posY - mapY) * deltaDistY;
    } else {
      stepY = 1;
      sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }
    // perform DDA
    while (hit == 0) {
      // jump to next map square, either in x-direction, or in y-direction
      if (sideDistX < sideDistY) {
        sideDistX += deltaDistX;
        mapX += stepX;
        side = 0;
      } else {
        sideDistY += deltaDistY;
        mapY += stepY;
        side = 1;
      }
      // Check if ray has hit a wall
      if (worldMap[mapX][mapY] > 0)
        hit = 1;
    }

    // Calculate distance projected on camera direction (Euclidean distance
    // would give fisheye effect!)
    if (side == 0)
      perpWallDist = (sideDistX - deltaDistX);
    else
      perpWallDist = (sideDistY - deltaDistY);

    // Calculate height of line to draw on screen
    int lineHeight = (int)(scrnHeight / perpWallDist);

    // calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + scrnHeight / 2;
    if (drawStart < 0)
      drawStart = 0;
    int drawEnd = lineHeight / 2 + scrnHeight / 2;
    if (drawEnd >= scrnHeight)
      drawEnd = scrnHeight - 1;

    // choose wall color
    SDL_Color color;
    color.a = 255;
    color.r = 0;
    color.b = 0;
    color.g = 0;

    switch (worldMap[mapX][mapY]) {
    case 1:
      color.r = 255;
      break; // red
    case 2:
      color.b = 255;
      break; // green
    case 3:
      color.g = 255;
      break; // blue
    case 4:
      color.r = 255;
      color.b = 255;
      color.g = 255;
      break; // white
    default:
      color.b = 255;
      color.g = 255;
      break; // yellow
    }

    // give x and y sides different brightness
    if (side == 1) {
      color.r = color.r / 4;
      color.b = color.b / 4;
      color.g = color.g / 4;
    }

    // draw the pixels of the stripe as a vertical line
    // verLine(x, drawStart, drawEnd, color);
    SDL_Point start;
    SDL_Point end;
    start.x = x;
    start.y = drawStart;
    end.x = x;
    end.y = drawEnd;

    // renderer->SDL_set_render_color(color);
    // renderer->addDrawEvent(start);
    // renderer->addDrawEvent(end);
    renderer->draw_line(color, start, end);
  }
  
}

// movment functions
void Raycaster::move_forward() {
  if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false)
    posX += dirX * moveSpeed;
  if (worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false)
    posY += dirY * moveSpeed;
}
void Raycaster::move_back() {
  if (worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false)
    posX -= dirX * moveSpeed;
  if (worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false)
    posY -= dirY * moveSpeed;
}
void Raycaster::move_right() {
  // both camera direction and camera plane must be rotated
  double oldDirX = dirX;
  dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
  dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
  double oldPlaneX = planeX;
  planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
  planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
}
void Raycaster::move_left() {
  // both camera direction and camera plane must be rotated
  double oldDirX = dirX;
  dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
  dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
  double oldPlaneX = planeX;
  planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
  planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
}
