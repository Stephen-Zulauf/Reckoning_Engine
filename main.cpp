#include "config.h"
#include "include/Window.h"
#include "include/Renderer.h"
#include "include/Raycaster.h"

/*flags */
bool g_FLAG_EXIT = false;
int g_SUCCESS;

/*SDL Window and renderer*/
Window* g_SDL_Window = nullptr;
Renderer* g_Renderer = nullptr;
Raycaster* g_Raycaster = nullptr;

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
    g_SDL_Window = new Window("Test", 800, 600);
    if(g_SDL_Window){
      g_Renderer = new Renderer(g_SDL_Window->getWindow());
    }
  }
  if(!g_Renderer){
    std::cout << "failed to create window and renderer" << std::endl;
    quit_program(1);
  }
  //create raycaster
  // g_Raycaster = new Raycaster(800, 600);
  //create 3d engine

}

void pipeline(){
  // build_vertex_shader();
  // build_fragment_shader();
  // link_shaders();
  // build_buffers();
  //load/create textures
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
        if(events.key.keysym.sym == SDLK_q){
          std::cout << "Exiting.." << std::endl;
          g_FLAG_EXIT = true;
        }
        if(events.key.keysym.sym == SDLK_UP){
          g_Raycaster->move_forward();
        }
        if(events.key.keysym.sym == SDLK_DOWN){
          g_Raycaster->move_back();
        }if(events.key.keysym.sym == SDLK_RIGHT){
          g_Raycaster->move_right();
        }if(events.key.keysym.sym == SDLK_LEFT){
          g_Raycaster->move_left();
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

  //pass draw calls to renderer
  // SDL_Point test1;
  // SDL_Point test2;
  // test1.x = (rand() % 800);
  // test1.y = (rand() % 600);
  // test2.x = (rand() % 800);
  // test2.y = (rand() % 600);
  // g_Renderer->addDrawEvent(test1);
  // g_Renderer->addDrawEvent(test2);
  // g_Renderer->updateRenderer();
  // g_Raycaster->RunFrame(g_Renderer);
  // g_Renderer->present();
  g_Renderer->updateRenderer();
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
