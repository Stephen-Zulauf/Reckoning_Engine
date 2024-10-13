#include "config.h"
#include "include/Window.h"
#include "include/Renderer.h"
#include "include/Doomed.h" 

/*flags */
bool g_FLAG_EXIT = false;
int g_SUCCESS;

/*SDL Window and renderer*/
Window* g_SDL_Window = nullptr;
Renderer* g_Renderer = nullptr;
Doomer* g_doomer = nullptr;


//resolution/scaling variables(TODO: move to doomer class?)
int resolution = 1;//0=160x120, 1=360x240, 2=640x480
int scrnWidth = 160;
int scrnHeight = 120;
int scrnWidthHalf = scrnWidth/2;
int scrnHeightHalf = scrnHeight/2;
int pixelScale = 4/resolution;
int SDL_win_w = (scrnWidth * pixelScale);
int SDL_win_h = (scrnHeight* pixelScale); 

/*gracefully exit*/
static void quit_program(int code){

  SDL_Quit();

  exit(code);
}

/*init SDL etc*/
void init(){

  //init SDL systems
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
    std::cout << "Could not init SDL" << std::endl;
    std::cout << "Error: " << SDL_GetError() << std::endl;
    quit_program(1);
  }else{
    g_SDL_Window = new Window("Test", SDL_win_w, SDL_win_h);
    if(g_SDL_Window){
      g_Renderer = new Renderer(g_SDL_Window->getWindow());
    }
  }
  if(!g_Renderer){
    std::cout << "failed to create window and renderer" << std::endl;
    quit_program(1);
  }
  //create doomed 3d engine
  g_doomer = new Doomer();

}

void pipeline(){
  srand(time(NULL));
  std::cout << "Pipeline success" << std::endl;
}

/*loop functions*/
void input(){
  SDL_Event events;
  while(SDL_PollEvent(&events) != 0){
    switch(events.type){
      case SDL_QUIT:
        std::cout << "Exiting" << std::endl;
        g_FLAG_EXIT = true;
        break;
      case SDL_KEYDOWN:
        if(events.key.keysym.sym == SDLK_c){
          std::cout << "Exiting.." << std::endl;
          g_FLAG_EXIT = true;
        }
        if(events.key.keysym.sym == SDLK_w){
          g_doomer->move_forward();
        }
        if(events.key.keysym.sym == SDLK_s){
          g_doomer->move_back();
        }if(events.key.keysym.sym == SDLK_d){
          g_doomer->move_right();
        }if(events.key.keysym.sym == SDLK_a){
          g_doomer->move_left();
        }if(events.key.keysym.sym == SDLK_q){
          g_doomer->move_strafe_left();
        }if(events.key.keysym.sym == SDLK_e){
          g_doomer->move_strafe_right();
        }     
        break;
      default:
        break;
    }
  }
}

void preDraw(){
  //set bg color
}

void draw(){

  g_Renderer->clear();
  g_Renderer->present();

}

void loop(){
    //loop on global flag
    while(!g_FLAG_EXIT){
      //handle input
      input();
      //calls before draw
      preDraw();
      //draw
      draw();
      //present renderer
    }
}

int main(int argc, char *argv[]){

  //init sdl opengl context etc.
  std::cout << "initializing sdl..." << std::endl;
  init();

  //run calculations/send draw events to renderer
  std::cout << "building pipeline..." << std::endl;
  pipeline();

  //main draw loop
  std::cout << "init main draw loop..." << std::endl;
  loop();

  //destroy contexts
  quit_program(0);
  
  return 0;
}
