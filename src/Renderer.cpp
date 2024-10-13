#include "../include/Renderer.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>

// check if renderer created
bool Renderer::checkRenderer() {
  if (this->renderer) {
    return true;
  } else {
    return false;
  }
}

// Return renderer instance
SDL_Renderer *Renderer::getRenderer() {
  if (this->renderer) {
    return this->renderer;
  } else {
    cout << "ERR no renderer instance" << endl;
    return nullptr;
  }
}
// Change background draw color
void Renderer::SDL_set_bg_color(SDL_Color newColor) {
  this->bgColor = newColor;
}

// Change renderer draw color
void Renderer::SDL_set_render_color(SDL_Color newColor) {
  this->render_color = newColor;
}

// add draw event
void Renderer::addDrawPoint(SDL_Point nPoint) {
  this->points.push_back(nPoint);
}

// clear points
void Renderer::clearDrawPoints() { this->points.clear(); }

// draw points buffer as lines
void Renderer::draw_lines(SDL_Color color) {
  SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLines(this->renderer, &this->points[0], this->points.size());
}
void Renderer::draw_lines(SDL_Color color, float scaleX, float scaleY) {
  SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderSetScale(this->renderer, scaleX, scaleY);
  SDL_RenderDrawLines(this->renderer, &this->points[0], this->points.size());
}

// draw points buffer as points
void Renderer::draw_points(SDL_Color color) {
  SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawPoints(this->renderer, &this->points[0], this->points.size());
}
void Renderer::draw_points(SDL_Color color, float scaleX, float scaleY) {
  SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderSetScale(this->renderer, scaleX, scaleY);
  SDL_RenderDrawPoints(this->renderer, &this->points[0], this->points.size());
}

// draw single line
void Renderer::draw_line(SDL_Color color, SDL_Point start, SDL_Point end) {
  SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(this->renderer, start.x, start.y, end.x, end.y);
}
void Renderer::draw_line(SDL_Color color, SDL_Point start, SDL_Point end,
                         float scaleX, float scaleY) {
  SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderSetScale(this->renderer, scaleX, scaleY);
  SDL_RenderDrawLine(this->renderer, start.x, start.y, end.x, end.y);
}

// draw a single point
void Renderer::draw_point(SDL_Color color, SDL_Point point) {
  SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawPoint(this->renderer, point.x, point.y);
}
void Renderer::draw_point(SDL_Color color, SDL_Point point, float scaleX,
                          float scaleY) {
  SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
  SDL_RenderSetScale(this->renderer, scaleX, scaleY);
  SDL_RenderDrawPoint(this->renderer, point.x, point.y);
}

// clear with background color
bool Renderer::clear() {
  if (SDL_SetRenderDrawColor(this->renderer, this->bgColor.r, this->bgColor.g,
                             this->bgColor.b, this->bgColor.a) == 0) {
    if (SDL_RenderClear(this->renderer) == 0) {

      return true;
    } else {
      cout << "ERR updateRenderer: RenderClear failed" << endl;
      return false;
    }
  } else {
    cout << "ERR updateRenderer: SetRenderDrawColor failed" << endl;
    return false;
  }
}

// present renderer
void Renderer::present() { SDL_RenderPresent(this->renderer); }
