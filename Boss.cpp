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
    left_done = true;

    SDL_FreeSurface(loadedSurface);
}

bool Boss::enter_boss_stage(int knight_mPosX)
{
    if(knight_mPosX >= 5400) return true;
    return false;
}

void Boss::move(int knight_mPosX, SDL_Rect SpriteClips[])
{
    if(left_done == true && charge == false && stunt == false && rage == false)
    {
        mTexture = left;
        mPosX--;
        currentClip = &SpriteClips[frame/10];
        frame++;
        if(frame/10 >= 4) frame = 0;
    }


    else if(right_done == true && charge == false && stunt == false && rage == false)
    {
        mTexture = right;
        mPosX++;

        currentClip = &SpriteClips[frame/10];
        frame++;
        if(frame/10 >= 4) frame = 0;

    }
    //Launching
    if(launch == true && stunt == false && rage == false)
    {
        currentClip = &SpriteClips[9];
        if(mTexture == left)
        {
            mPosX-=5;
            if(mPosX >= 6235 && mPosX <= 6240)
            {
                launch = false;
                charge = false;
                left_done = false;
                right_done = true;
                currentClip = &SpriteClips[0];
                charging = 200;
                counting_stunt++;
            }
        }
        else if(mTexture == right)
        {
            mPosX+=5;
            if(mPosX >= 7000 && mPosX <= 7005)
            {
                launch = false;
                charge = false;
                right_done = false;
                left_done = true;
                currentClip = &SpriteClips[0];
                charging = 200;
                counting_stunt++;
            }
        }
    }
    //Charging
    else if((abs(mPosX - knight_mPosX) <= 300 || charge == true) && stunt == false && rage == false)
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

    if(health.w >= 100 && health.w <= 110)//Rage
    {
        mPosY = 190;
        rage = true;
        currentClip = &SpriteClips[raging/50];
        raging++;
        if(raging/50 > 18 && counting_rage == 0)
        {
            raging = 850;
            counting_rage++;
        }
        else if(raging/50 > 19 && counting_rage == 1)
        {
            raging = 160;
            counting_rage++;
        }
        if(raging/8 >= 20 && counting_rage == 2)
        {
            currentClip = &SpriteClips[raging/8];
            if(mTexture == left) mPosX = 6300;
        }
        if(raging/8 > 27 && counting_rage == 2)
        {
            rage = false;
            health.w-=11;
            if(mTexture == left) mPosX = 7000;
            raging = 850;
            counting_rage = 0;
            counting_stunt = 0;
            mPosY = 190;
        }
    }

    //Stunning
    if((counting_stunt == 3 || stunt == true) && rage == false)
    {
        if(counting_stunt == 3 && stunning == 110 && mTexture == right) mTexture = left;
        else if(counting_stunt == 3 && stunning == 110 && mTexture == left) mTexture = right;

        mPosY = 190;
        stunt = true;
        currentClip = &SpriteClips[stunning/10];
        stunning++;
        if(stunning/10 > 12)
        {
            stunning = 110;
            counting_stunt++;
        }
        if(counting_stunt == 15)
        {
            mPosY = 150;
            stunt = false;
            counting_stunt = 0;
        }
    }
}

void Boss::render(int camX, int camY, SDL_Renderer* renderer, SDL_Rect SpriteClips[])
{
    health.x = mPosX + currentClip->w/2 - 100 - camX;
    health.y = mPosY;

    if(currentClip == &SpriteClips[20] || currentClip == &SpriteClips[21] || currentClip == &SpriteClips[22] || currentClip == &SpriteClips[23] || currentClip == &SpriteClips[24] || currentClip == &SpriteClips[25] || currentClip == &SpriteClips[26] || currentClip == &SpriteClips[27])
    {
        if(mTexture == right) health.x = 50;
        else if(mTexture == left) health.x = 700;
        health.y+=80;
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

