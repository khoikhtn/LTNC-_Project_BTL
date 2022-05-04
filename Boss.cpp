#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<math.h>

#include "Boss.h"

void Boss::loadtexture(string path_right, string path_left, SDL_Renderer* renderer)
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

bool Boss::enter_boss_stage(int knight_mPosX)
{
    if(knight_mPosX >= 900) return true;
    return false;
}

void Boss::move(int knight_mPosX, SDL_Rect SpriteClips[])
{
    if(knight_mPosX < mPosX && charge == false)
    {
        mTexture = left;
        if(mPosX - knight_mPosX >= 20)
        {
            mPosX--;
            currentClip = &SpriteClips[frame/10];
            frame++;
            if(frame/10 >= 4) frame = 0;
        }
    }

    else if(knight_mPosX >= mPosX && charge == false)
    {
        mTexture = right;
        if(knight_mPosX - mPosX >= 20)
        {
            mPosX++;
            currentClip = &SpriteClips[frame/10];
            frame++;
            if(frame/10 >= 4) frame = 0;
        }
    }

    if(launch == true)
    {
        currentClip = &SpriteClips[9];
        if(mTexture == left)
        {
            mPosX-=5;
            if(mPosX >= 1000 && mPosX <= 1004)
            {
                launch = false;
                charge = false;
                currentClip = &SpriteClips[0];
                charging = 200;
            }
        }
        else if(mTexture == right)
        {
            mPosX+=5;
            if(mPosX >= 1800 && mPosX <= 1804)
            {
                launch = false;
                charge = false;
                currentClip = &SpriteClips[0];
                charging = 200;
            }
        }
    }

    else if((abs(mPosX - knight_mPosX) >= 300 && abs(mPosX - knight_mPosX) <= 304) || charge == true)
    {
        charge = true;
        currentClip = &SpriteClips[charging/50];
        charging++;
        mPosY = 190;
        if(charging/50 > 4)
        {
            launch = true;
            if(mTexture == right) mPosX+=100;
            else mPosX-=100;
            mPosY = 150;
        }
    }
}

void Boss::render(int camX, int camY, SDL_Renderer* renderer)
{
    health.x = mPosX - health.w/2 + currentClip->w/2 - camX;
    health.y = mPosY;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &health);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect quadrad = {mPosX - camX, mPosY, currentClip->w, currentClip->h};
    SDL_RenderCopy(renderer, mTexture, currentClip, &quadrad);
}

