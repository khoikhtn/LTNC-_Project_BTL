#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

#include "Monster.h"

void Monster::loadtexture(SDL_Renderer* renderer)
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
        if(mPosX - knight_mPosX <= 300 && mPosX - knight_mPosX >= 70)
        {
            mPosX--;
            currentClip = &SpriteClips[frame/10];
            frame++;
            if(frame/10 >= 4) frame = 0;
        }
        if(mPosX - knight_mPosX < 70)
        {
            currentClip = &SpriteClips[fight_scene/50];
            fight_scene++;
            if(fight_scene/50 >= 6) fight_scene = 200;
        }
    }
    else
    {
        mTexture = right;
        if(knight_mPosX - mPosX >= 90 && knight_mPosX - mPosX <= 400)
        {
            mPosX++;
            currentClip = &SpriteClips[frame/10];
            frame++;
            if(frame/10 >= 4) frame = 0;
        }
        if(knight_mPosX - mPosX < 90)
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
    if(path_right == "bigguy2.png" && path_left == "bigguy1.png")
    {
        health.y = mPosY + 40;
    }
    else if(path_right == "monster2.png" && path_left == "monster1.png")
    {
        if(mTexture == left) health.x -= 35;
        else if(mTexture == right) health.x += 20;
        health.y = mPosY + 120;
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &health);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect quadrad = {mPosX - camX, mPosY, currentClip->w, currentClip->h};
    SDL_RenderCopy(renderer, mTexture, currentClip, &quadrad);
}

