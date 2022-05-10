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
        else if(mPosX - knight_mPosX < 70)
        {
            currentClip = &SpriteClips[fight_scene/50];
            fight_scene++;
            if(fight_scene/50 >= 6) fight_scene = 200;
        }
        else
        {
            currentClip = &SpriteClips[standing/20];
            standing++;
            if(standing/20 > 12) standing = 220;
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
        else if(knight_mPosX - mPosX < 90)
        {
            currentClip = &SpriteClips[fight_scene/50];
            fight_scene++;
            if(fight_scene/50 >= 6) fight_scene = 200;
        }
        else
        {
            currentClip = &SpriteClips[standing/20];
            standing++;
            if(standing/20 > 12) standing = 220;
        }
    }
    if(health.w == 0)
    {
        currentClip = &SpriteClips[13];
        health_border.w = 0;
    }
}

void Monster::render(int camX, int camY, SDL_Renderer* renderer)
{
    health.x = mPosX + currentClip->w/2 - camX;
    if(path_right == "bigguy2.png" && path_left == "bigguy1.png")
    {
        health.x -= 30;
        health.y = mPosY + 40;
    }
    else if(path_right == "monster2.png" && path_left == "monster1.png")
    {
        if(mTexture == left) health.x -= 55;
        else if(mTexture == right) health.x -= 10;

        health.y = mPosY + 120;
    }

    health_border.x = health.x - 2;
    health_border.y = health.y - 1;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, &health_border);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &health);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect quadrad = {mPosX - camX, mPosY, currentClip->w, currentClip->h};
    SDL_RenderCopy(renderer, mTexture, currentClip, &quadrad);
}

