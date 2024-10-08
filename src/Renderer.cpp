#include "../include/Renderer.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>

//check if renderer created
bool Renderer::checkRenderer() {
	if (this->renderer) {
		return true;
	}
	else {
		return false;
	}
}

//Return renderer instance
SDL_Renderer* Renderer::getRenderer() {
	if (this->renderer) {
		return this->renderer;
	}
	else {
		cout << "ERR no renderer instance" << endl;
		return nullptr;
	}
}
//Change background draw color
void Renderer::SDL_set_bg_color(SDL_Color newColor){
  this->bgColor = newColor;
}

//Change renderer draw color
void Renderer::SDL_set_render_color(SDL_Color newColor){
  this->render_color = newColor;
}

//add draw event
void Renderer::addDrawEvent(SDL_Point nEvent) {
	this->points.push_back(nEvent);
}

//Update renderer
bool Renderer::updateRenderer() {

	if (SDL_SetRenderDrawColor(this->renderer, this->bgColor.r, this->bgColor.g, this->bgColor.b, this->bgColor.a) == 0) {
		if (SDL_RenderClear(this->renderer) == 0) {
			//draw queue here
			if(SDL_SetRenderDrawColor(this->renderer, this->render_color.r, this->render_color.g, this->render_color.b, this->render_color.a)<0){
			  std::cout << "Renderer failed to set draw color: " << SDL_GetError() << std::endl;
			}
			SDL_RenderDrawLines(this->renderer, &this->points.data()[0], this->points.size());

			SDL_RenderPresent(this->renderer);

			return true;
		}
		else {
			cout << "ERR updateRenderer: RenderClear failed" << endl;
			return false;
		}
	}
	else {
		cout << "ERR updateRenderer: SetRenderDrawColor failed" << endl;
		return false;
	}
}


