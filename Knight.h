#ifndef KNIGHT__H_
#define KNIGHT__H_

#include<iostream>
#include<SDL.h>

#include "Monster.h"
#include "Boss.h"
#include "SDL_utils.h"

using namespace std;

class Monster;
class Boss;
class Knight
{
    public:
        SDL_Texture* right;
        SDL_Texture* left;
        SDL_Texture* mTexture;
        SDL_Rect* currentClip;
        SDL_Rect health_border = {0, 0, 54, 5};
        SDL_Rect health = {0, 0, 50, 3};
        SDL_Rect power_border = {0, 0, 54, 5};
        SDL_Rect power = {0, 0, 0, 3};

        int frame = 0;
        int standing = 100;
        int mPosX = 0, mPosY = 110;
        int mVelX = 0;

        bool super_slash = false, direction = false;
        int slash_frame;
        int slash_distance;

        void loadtexture(string path_right, string path_left, SDL_Renderer* renderer);
        void handleEvent(SDL_Rect SpriteClips[], Monster monster[], Boss &boss, SDL_Renderer* renderer, SDL_Texture* mapp, SDL_Texture* item, SDL_Texture* superslash_left, SDL_Texture* superslash_right, SDL_Rect camera, int LEVEL_WIDTH, int LEVEL_HEIGHT);
        void stand_still(SDL_Event &e);

        void hits_monster_status(Monster &monster, SDL_Rect SpriteClips[]);//Chém quái
        void being_hit_status(Monster &monster, SDL_Rect SpriteClips[]);//Bị quái đấm

        void hits_boss_status(Boss &boss ,SDL_Rect SpriteClips[]);//Chém boss
        void being_hit_by_boss_status(Boss &boss, SDL_Rect SpriteClips[]);//Bị boss đấm

        void render(int camX, int camY, SDL_Renderer* renderer, SDL_Rect SpriteCLips[]);
};

#endif
