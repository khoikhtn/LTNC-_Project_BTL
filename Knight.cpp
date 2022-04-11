#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

#include "Knight.h"

void Knight::loadtexture(string path_right, string path_left, SDL_Renderer* renderer)
{
    SDL_Surface* loadedSurface = IMG_Load(path_right.c_str());
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
    right = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    loadedSurface = IMG_Load(path_left.c_str());
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
    left = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    mTexture = right;

    SDL_FreeSurface(loadedSurface);

}

void Knight::handleEvent(SDL_Event &e, SDL_Rect SpriteClips[], Monster &monster, SDL_Renderer* renderer, SDL_Texture* mapp, SDL_Rect camera)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_RIGHT: mVelX++; mTexture = right; break;
            case SDLK_LEFT: mVelX--; mTexture = left; break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_RIGHT: mVelX--; break;
            case SDLK_LEFT: mVelX++; break;
        }
    }

    if(e.key.keysym.sym == SDLK_RIGHT)
    {
        currentClip = &SpriteClips[frame/4];
        frame++;
        if(frame/4 >= 4) frame = 0;
    }

    else if(e.key.keysym.sym == SDLK_LEFT)
    {
        currentClip = &SpriteClips[frame/4];
        frame++;
        if(frame/4 >= 4) frame = 0;
    }

    if(e.key.keysym.sym == SDLK_z && e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        int fight_scene = 40;
        while(fight_scene/10 <= 5)
        {
            currentClip = &SpriteClips[fight_scene/10];

            SDL_RenderClear(renderer);
            render_map(renderer, mapp, camera);
            this->render(camera.x, camera.y, renderer);
            this->monster_continue(monster, SpriteClips);
            monster.render(camera.x, camera.y, renderer);
            SDL_RenderPresent(renderer);
            fight_scene++;
        }
        SDL_RenderClear(renderer);
        currentClip = &SpriteClips[frame/4];
    }
}

void Knight::move()
{
    mPosX += mVelX*3;
}

void Knight::render(int camX, int camY, SDL_Renderer* renderer)
{
    health.x = mPosX - health.w/2 + currentClip->w/2 - camX;
    health.y = mPosY + 150;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &health);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect quadrad = {mPosX - camX, mPosY - camY, currentClip->w, currentClip->h};
    SDL_RenderCopy(renderer, mTexture, currentClip, &quadrad);
}

void Knight::monster_continue(Monster &monster, SDL_Rect SpriteClips[])
{
    if(monster.mPosX > mPosX)
    {
        if(monster.mPosX - mPosX <= 400 && monster.mPosX - mPosX >=50)
        {
            monster.mPosX--;
            monster.currentClip = &SpriteClips[monster.frame/4];
            monster.frame++;
            if(monster.frame/4 >= 4) monster.frame = 0;
        }

        if(monster.mPosX - mPosX < 50)
        {
            monster.currentClip = &SpriteClips[monster.fight_scene/50];
            monster.fight_scene++;
            if(monster.fight_scene/50 >= 6) monster.fight_scene = 200;
        }
    }

    else
    {
        if(mPosX - monster.mPosX >= 70 && mPosX - monster.mPosX <= 400)
        {
            monster.mPosX++;
            monster.currentClip = &SpriteClips[monster.frame/4];
            monster.frame++;
            if(monster.frame/4 >= 4) monster.frame = 0;
        }
        if(mPosX - monster.mPosX < 70)
        {
            monster.currentClip = &SpriteClips[monster.fight_scene/50];
            monster.fight_scene++;
            if(monster.fight_scene/50 >= 6) monster.fight_scene = 200;
        }
    }
}
