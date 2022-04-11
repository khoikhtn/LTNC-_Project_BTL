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

void Monster::move(Knight knight, SDL_Rect SpriteClips[])
{
    if(knight.mPosX < mPosX)
    {
        mTexture = left;
        if(mPosX - knight.mPosX <= 400 && mPosX - knight.mPosX >= 50)
        {
            mPosX--;
            currentClip = &SpriteClips[frame/4];
            frame++;
            if(frame/4 >= 4) frame = 0;
        }
        if(mPosX - knight.mPosX < 50)
        {
            currentClip = &SpriteClips[fight_scene/50];
            fight_scene++;
            if(fight_scene/50 >= 6) fight_scene = 200;
        }
    }
    else
    {
        mTexture = right;
        if(knight.mPosX - mPosX >= 70 && knight.mPosX - mPosX <= 400)
        {
            mPosX++;
            currentClip = &SpriteClips[frame/4];
            frame++;
            if(frame/4 >= 4) frame = 0;
        }
        if(knight.mPosX - mPosX < 70)
        {
            currentClip = &SpriteClips[fight_scene/50];
            fight_scene++;
            if(fight_scene/50 >= 6) fight_scene = 200;
        }
    }
}

void Monster::render(int camX, int camY, SDL_Renderer* renderer)
{
    SDL_Rect quadrad = {mPosX - camX, mPosY, currentClip->w, currentClip->h};
    SDL_RenderCopy(renderer, mTexture, currentClip, &quadrad);
}
