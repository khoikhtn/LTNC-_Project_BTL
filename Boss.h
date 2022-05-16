#ifndef BOSS__H_
#define BOSS__H_

#include<iostream>
#include "Knight.h"

using namespace std;

class Knight;

class Boss
{
    public:
        SDL_Texture* right;
        SDL_Texture* left;
        SDL_Texture* mTexture;
        SDL_Rect* currentClip;
        SDL_Rect health_border = {0, 0, 204, 5};
        SDL_Rect health = {0, 0, 200, 3};
        SDL_Rect SpriteClips[10];

        int frame = 0, fight_scene;
        int mPosX  = 7200, mPosY = 150;
        int charging = 200, stunning = 110, counting = 0;

        bool charge = false, launch = false, stunt = false;

        bool enter_boss_stage(int knight_mPosX);

        void loadtexture(string path_right, string path_left, SDL_Renderer* renderer);
        void move(int knight_mPosX, SDL_Rect SpriteClips[]);
        void render(int camX, int camY, SDL_Renderer* renderer);
};

#endif
