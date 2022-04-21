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
        SDL_Rect health = {0, 0, 100, 3};

        int frame = 0, fight_scene;
        int mPosX  = 1000, mPosY = 190;
        string path_right, path_left;

        void loadtexture(SDL_Renderer* renderer);
        void move(int knight_mPosX, SDL_Rect SpriteClips[]);
        void render(int camX, int camY, SDL_Renderer* renderer);
};

#endif
