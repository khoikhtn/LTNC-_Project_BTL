#ifndef KNIGHT__H_
#define KNIGHT__H_

#include<iostream>
#include<SDL.h>
#include "Monster.h"
#include "SDL_utils.h"

using namespace std;

class Monster;
class Knight
{
    public:
        SDL_Texture* right;
        SDL_Texture* left;
        SDL_Texture* mTexture;
        SDL_Rect* currentClip;
        SDL_Rect health = {0, 0, 50, 3};

        int frame = 0;
        int mPosX = 0, mPosY = 150;
        int mVelX = 0, mVelY = 0;

        void loadtexture(string path_right, string path_left, SDL_Renderer* renderer);
        void handleEvent(SDL_Event &e, SDL_Rect SpriteClips[], Monster monster[], SDL_Renderer* renderer, SDL_Texture* mapp, SDL_Rect camera, int LEVEL_WIDTH, int LEVEL_HEIGHT);
        void move(SDL_Event &e);

        void hits_monster_status(Monster &monster, SDL_Rect SpriteClips[]);//Chém quái
        void being_hit_status(Monster &monster, SDL_Rect SpriteClips[]);//Bị đấm

        void render(int camX, int camY, SDL_Renderer* renderer);
};

#endif
