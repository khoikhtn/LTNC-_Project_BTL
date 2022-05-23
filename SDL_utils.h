#ifndef SDL_UTILS__H_
#define SDL_UTILS__H_

#include<SDL.h>
#include<SDL_image.h>
#include<algorithm>
#include<iostream>

#include "Knight.h"
#include "Monster.h"
#include "Boss.h"

class Knight;
class Monster;
class Boss;

using namespace std;
void init(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);

SDL_Texture* load_bg(SDL_Renderer* renderer, string path);

void render_map(SDL_Renderer* renderer, SDL_Texture* mapp, SDL_Rect camera);
void render_button(SDL_Renderer* renderer, SDL_Texture* button1, SDL_Texture* button2, SDL_Rect currentButton1, SDL_Rect currentButton2);
void back_button(SDL_Renderer* renderer, SDL_Texture* backbut, SDL_Rect current_back);
int render_super_slash(SDL_Renderer* renderer, SDL_Texture* slash_left, SDL_Texture* slash_right, int frame, int dis, bool direction, int camX, Monster monster[], Boss &boss);
int meteo_incoming(SDL_Texture* meteo, SDL_Renderer* renderer, int frame, int camX, int i);
int render_meteo(int knight_mPosX, int rep, int &meteo_frame, SDL_Texture* danger_sign, SDL_Texture* meteo, SDL_Renderer* renderer, int camX, int &knight_health, int i);
void render_items(SDL_Renderer* renderer, SDL_Texture* item, int camX);

void Sprite(SDL_Rect SpriteClips[]);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

#endif
