#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

#include "Monster.h"

void Monster::loadtexture(string path_right, string path_left, SDL_Renderer* renderer)
{
    SDL_Surface* loadedSurface = IMG_Load(path_right.c_str());
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
    right = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    loadedSurface = IMG_Load(path_left.c_str());
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
    left = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    mTexture = left;

    SDL_FreeSurface(loadedSurface);
}

void Monster::move(int knight_mPosX, SDL_Rect SpriteClips[])
{
    if(knight_mPosX < mPosX)
    {
        mTexture = left;
        if(mPosX - knight_mPosX <= 400 && mPosX - knight_mPosX >= 45)
        {
            mPosX--;
            currentClip = &SpriteClips[frame/4];
            frame++;
            if(frame/4 >= 4) frame = 0;
        }
        if(mPosX - knight_mPosX < 45)
        {
            currentClip = &SpriteClips[fight_scene/50];
            fight_scene++;
            if(fight_scene/50 >= 6) fight_scene = 200;
        }
    }
    else
    {
        mTexture = right;
        if(knight_mPosX - mPosX >= 40 && knight_mPosX - mPosX <= 400)
        {
            mPosX++;
            currentClip = &SpriteClips[frame/4];
            frame++;
            if(frame/4 >= 4) frame = 0;
        }
        if(knight_mPosX - mPosX < 40)
        {
            currentClip = &SpriteClips[fight_scene/50];
            fight_scene++;
            if(fight_scene/50 >= 6) fight_scene = 200;
        }
    }
    if(health.w == 0) currentClip = &SpriteClips[7];
}

void Monster::render(int camX, int camY, SDL_Renderer* renderer)
{
    health.x = mPosX - health.w/2 + currentClip->w/2 - camX;
    health.y = mPosY + 80;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &health);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect quadrad = {mPosX - camX, mPosY, currentClip->w, currentClip->h};
    SDL_RenderCopy(renderer, mTexture, currentClip, &quadrad);
}

