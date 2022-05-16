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
    if(knight_mPosX >= 5400) return true;
    return false;
}

void Boss::move(int knight_mPosX, SDL_Rect SpriteClips[])
{
    if(knight_mPosX < mPosX && charge == false && stunt == false)
    {
        mTexture = left;
        mPosX--;
        currentClip = &SpriteClips[frame/10];
        frame++;
        if(frame/10 >= 4) frame = 0;
        }


    else if(knight_mPosX >= mPosX && charge == false && stunt == false)
    {
        mTexture = right;
        mPosX++;
        currentClip = &SpriteClips[frame/10];
        frame++;
        if(frame/10 >= 4) frame = 0;

    }
    //Launching
    if(launch == true && stunt == false)
    {
        currentClip = &SpriteClips[9];
        if(mTexture == left)
        {
            mPosX-=5;
            if(mPosX >= 6235 && mPosX <= 6240)
            {
                launch = false;
                charge = false;
                currentClip = &SpriteClips[0];
                charging = 200;
                counting++;
            }
        }
        else if(mTexture == right)
        {
            mPosX+=5;
            if(mPosX >= 7000 && mPosX <= 7005)
            {
                launch = false;
                charge = false;
                currentClip = &SpriteClips[0];
                charging = 200;
                counting++;
            }
        }
    }
    //Charging
    else if((abs(mPosX - knight_mPosX) <= 300 || charge == true) && stunt == false)
    {
        charge = true;
        currentClip = &SpriteClips[charging/50];
        charging++;
        mPosY = 190;
        if(charging/50 > 4)
        {
            launch = true;
            if(mTexture == right) mPosX+=50;
            else mPosX-=50;
            mPosY = 150;
        }
    }

    //Stunning
    if(counting == 3 || stunt == true)
    {
        if(counting == 3 && stunning == 110 && mTexture == right) mTexture = left;
        else if(counting == 3 && stunning == 110 && mTexture == left) mTexture = right;

        mPosY = 190;
        stunt = true;
        currentClip = &SpriteClips[stunning/10];
        stunning++;
        if(stunning/10 > 12)
        {
            stunning = 110;
            counting++;
        }
        if(counting == 15)
        {
            mPosY = 150;
            stunt = false;
            counting = 0;
        }
    }
}

void Boss::render(int camX, int camY, SDL_Renderer* renderer)
{
    health.x = mPosX + currentClip->w/2 - 100 - camX;
    health.y = mPosY;

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

