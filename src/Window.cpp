#include "../include/Window.h"

//check if window created
bool Window::checkWindow() {
	if (this->window) {
		return true;
	}
	else {
		return false;
	}
}

//return the window instance
SDL_Window* Window::getWindow() {
	if (this->window) {
		return this->window;
	}
	else {
		cout << "ERR no window instance" << endl;
		return nullptr;
	}
}
