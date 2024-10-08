#ifndef WINDOW_H
#define WINDOW_H

#include "../config.h"

using std::cout;
using std::endl;
using std::string;

class Window {
private:
	string title = "default";
	int width = 720;
	int height = 720;
	int posX = 0;
	int posY = 0;
	SDL_Window* window = nullptr;

public:
	Window() {

	}
	//default centered postion
	Window(string nTitle, int nWidth, int nHeight) {
	  this->title = nTitle;
		width = nWidth;
		height = nHeight;
		window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
		if(!window){
		  std::cout << "Window Failed to create window: " << SDL_GetError() << std::endl;
		}
	}
	//specify position
	Window(string nTitle, int nPosx, int nPosy, int nWidth, int nHeight) {
	  this->title = nTitle;
		posX = nPosx;
		posY = nPosy;
		width = nWidth;
		height = nHeight;
		window = SDL_CreateWindow(title.c_str(), posX, posY, width, height, SDL_WINDOW_SHOWN);
    if(!window){
		  std::cout << "Window Failed to create window: " << SDL_GetError() << std::endl;
		}	
	}
	//copy
	Window(Window &copy) {
	  copy.title = this->title;
		copy.posX = this->posX;
		copy.posY = this->posY;
		copy.width = this->width;
		copy.height = this->height;
		copy.window = SDL_CreateWindow(title.c_str(), posX, posY, width, height, SDL_WINDOW_SHOWN);
	}
	~Window() {
		if (this->window) {
			SDL_DestroyWindow(this->window);
		}
	}

	//check if window created
	bool checkWindow();

	//return the window instance
	SDL_Window* getWindow();
};

#endif
