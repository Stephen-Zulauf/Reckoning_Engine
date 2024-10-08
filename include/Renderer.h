#ifndef RENDERER_H
#define RENDERER_H

#include "../config.h"
#include <vector>

using std::cout;
using std::endl;

//draw event struct; holds points andcolor change

class Renderer {
private:
	SDL_Color bgColor;
	SDL_Color render_color;
	SDL_Renderer* renderer = nullptr;
	SDL_Window* window = nullptr;
	//vector of points to be drawn each frame
	std::vector<SDL_Point> points;

public:
	//default black screen
	Renderer(SDL_Window* nWindow) {
		this->bgColor.r = 0;
		this->bgColor.g = 0;
		this->bgColor.b = 0;
		this->bgColor.a = 255;

		this->render_color.r = 255;
		this->render_color.g = 255;
		this->render_color.b = 255;
		this->render_color.a = 255;
		window = nWindow;
		renderer = SDL_CreateRenderer(nWindow, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
    		  cout << "Renderer SDL_Error at create renderer: " << SDL_GetError() << endl;
    }	
  }
	//specify background
	Renderer(SDL_Window* nWindow, SDL_Color bgColor, SDL_Color rendColor) {
		this->bgColor = bgColor;
		window = nWindow;
		renderer = SDL_CreateRenderer(nWindow, -1, SDL_RENDERER_ACCELERATED);
		if(!renderer){
		  cout << "Renderer SDL_Error at create renderer: " << SDL_GetError() << endl;
		}
	}
	~Renderer() {
		if (renderer) {
			SDL_DestroyRenderer(this->renderer);
		}
	}

	//check if renderer created
	bool checkRenderer();

	//Return renderer instance
	SDL_Renderer* getRenderer();

	//Change background draw color
	void SDL_set_bg_color(SDL_Color newColor);

  //Change renderer draw color
	void SDL_set_render_color(SDL_Color newColor);

  //add draw event
  void addDrawEvent(SDL_Point nEvent);

	//Update renderer
	bool updateRenderer();

};

#endif
