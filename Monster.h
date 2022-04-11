#ifndef MONSTER__H_
#define MONSTER__H_

#include<iostream>
#include "Knight.h"

using namespace std;

class Knight;
class Monster
{
    public:
        SDL_Texture* right;
        SDL_Texture* left;
        SDL_Texture* mTexture;
        SDL_Rect* currentClip;
        SDL_Rect health = {0, 0, 50, 5};
        SDL_Rect SpriteClips[5];

        int frame = 0, fight_scene = 200;
        int mPosX = 500, mPosY = 230;

        void loadtexture(string path_right, string path_left, SDL_Renderer* renderer);
        void move(Knight knight, SDL_Rect SpriteClips[]);
        void render(int camX, int camY, SDL_Renderer* renderer);
};

#endif
