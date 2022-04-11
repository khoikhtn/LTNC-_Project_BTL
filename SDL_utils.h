#ifndef SDL_UTILS__H_
#define SDL_UTILS__H_

#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
using namespace std;
void init(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
SDL_Texture* load_map(SDL_Renderer* renderer, string path);
void render_map(SDL_Renderer* renderer, SDL_Texture* mapp, SDL_Rect camera);
void Sprite(SDL_Rect SpriteClips[]);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

#endif
