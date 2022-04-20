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

void Knight::handleEvent(SDL_Event &e, SDL_Rect SpriteClips[], Monster monster[], SDL_Renderer* renderer, SDL_Texture* mapp, SDL_Rect camera, int LEVEL_WIDTH, int LEVEL_HEIGHT)
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

    //Left and right
    if(e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT)
    {
        currentClip = &SpriteClips[frame/4];
        frame++;
        if(frame/4 >= 4) frame = 0;
    }

    //Up: Jump
    if(e.key.keysym.sym == SDLK_UP && e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        currentClip = &SpriteClips[4];
        int i=1;
        while(i<=11)
        {
            mPosY-=i;
            mPosX+=mVelX*2;
            for(int i=0; i<=3; i++) monster[i].move(mPosX, SpriteClips);
            camera.x = mPosX - camera.w/2;
            camera.y = mPosY - camera.h/2;
            if(camera.x < 0)
            {
                camera.x = 0;
            }
            if(camera.y < 0)
            {
                camera.y = 0;
            }
            if(camera.x > LEVEL_WIDTH - camera.w)
            {
                camera.x = LEVEL_WIDTH - camera.w;
            }
            if(camera.y > LEVEL_HEIGHT - camera.h)
            {
                camera.y = LEVEL_HEIGHT - camera.h;
            }

            SDL_RenderClear(renderer);
            render_map(renderer, mapp, camera);
            this->render(camera.x, camera.y, renderer, SpriteClips);
            for(int i=0; i<=3; i++) monster[i].render(camera.x, camera.y, renderer);
            SDL_RenderPresent(renderer);
            i++;
        }
        i=1;
        while(i<=11)
        {
            mPosY+=i;
            mPosX+=mVelX*2;
            for(int i=0; i<=3; i++) monster[i].move(mPosX, SpriteClips);
            camera.x = mPosX - camera.w/2;
            camera.y = mPosY - camera.h/2;
            if(camera.x < 0)
            {
                camera.x = 0;
            }
            if(camera.y < 0)
            {
                camera.y = 0;
            }
            if(camera.x > LEVEL_WIDTH - camera.w)
            {
                camera.x = LEVEL_WIDTH - camera.w;
            }
            if(camera.y > LEVEL_HEIGHT - camera.h)
            {
                camera.y = LEVEL_HEIGHT - camera.h;
            }

            SDL_RenderClear(renderer);
            render_map(renderer, mapp, camera);
            this->render(camera.x, camera.y, renderer, SpriteClips);
            for(int i=0; i<=3; i++) monster[i].render(camera.x, camera.y, renderer);
            SDL_RenderPresent(renderer);
            i++;
        }
        currentClip = &SpriteClips[frame/4];
    }

    //Z: Attack
    if(e.key.keysym.sym == SDLK_z && e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        int fight_scene = 70;
        while(fight_scene/10 <= 8)
        {
            currentClip = &SpriteClips[fight_scene/10];
            for(int i=0; i<=3; i++) monster[i].move(mPosX, SpriteClips);
            for(int i=0; i<=3; i++) this->hits_monster_status(monster[i], SpriteClips);

            camera.x = mPosX - camera.w/2;
            camera.y = mPosY - camera.h/2;
            if(camera.x < 0)
            {
                camera.x = 0;
            }
            if(camera.y < 0)
            {
                camera.y = 0;
            }
            if(camera.x > LEVEL_WIDTH - camera.w)
            {
                camera.x = LEVEL_WIDTH - camera.w;
            }
            if(camera.y > LEVEL_HEIGHT - camera.h)
            {
                camera.y = LEVEL_HEIGHT - camera.h;
            }
            SDL_RenderClear(renderer);
            render_map(renderer, mapp, camera);
            this->render(camera.x, camera.y, renderer, SpriteClips);
            for(int i=0; i<=3; i++) monster[i].render(camera.x, camera.y, renderer);
            SDL_RenderPresent(renderer);
            fight_scene++;
        }
        currentClip = &SpriteClips[frame/4];
    }
}

void Knight::hits_monster_status(Monster &monster, SDL_Rect SpriteClips[])
{
    if(mPosX < monster.mPosX && mTexture == right)
    {
        if(monster.mPosX - mPosX > 30 && monster.mPosX - mPosX < 180 && currentClip == &SpriteClips[8])
        {
            monster.currentClip = &SpriteClips[6];
            monster.mPosX+=3;
            if(monster.health.w != 0) monster.health.w--;
            if(monster.health.w == 0) monster.currentClip = &SpriteClips[7];
        }
    }
    else if(mPosX >= monster.mPosX && mTexture == left)
    {
        if(mPosX - monster.mPosX > 0 && mPosX - monster.mPosX < 120 && currentClip == &SpriteClips[8])
        {
            monster.currentClip = &SpriteClips[6];
            monster.mPosX-=3;
            if(monster.health.w != 0) monster.health.w--;
            if(monster.health.w == 0) monster.currentClip = &SpriteClips[7];
        }
    }
}

void Knight::being_hit_status(Monster &monster, SDL_Rect SpriteClips[])
{
    if(mPosX < monster.mPosX)
    {
        if(monster.mPosX - mPosX > 0 && monster.mPosX - mPosX < 90 && monster.fight_scene == 250)
        {
            if(health.w != 0 && monster.currentClip != &SpriteClips[7]) health.w-=5;
        }
    }
    else
    {
        if(mPosX - monster.mPosX > 0 && mPosX - monster.mPosX < 50 && monster.fight_scene == 250)
        {
            if(health.w != 0 && monster.currentClip != &SpriteClips[7]) health.w-=5;
        }
    }
}

void Knight::move(SDL_Event &e, SDL_Rect SpriteClip[])
{
    if(e.type == SDL_MOUSEMOTION);
    else mPosX += mVelX*3;
}

void Knight::render(int camX, int camY, SDL_Renderer* renderer, SDL_Rect SpriteClips[])
{
    if(mTexture == right)
    {
        health.x = mPosX - health.w/2 + currentClip->w/2 + 45 - camX;
        if(currentClip == &SpriteClips[8]) health.x -= 50;
    }
    else
    {
        health.x = mPosX - health.w/2 + currentClip->w/2 + 20 - camX;
        if(currentClip == &SpriteClips[8]) health.x -= 50;
    }

    health.y = mPosY + 160;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &health);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect quadrad = {mPosX - camX, mPosY - camY, currentClip->w, currentClip->h};
    SDL_RenderCopy(renderer, mTexture, currentClip, &quadrad);
}

