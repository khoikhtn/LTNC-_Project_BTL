#include<iostream>
#include<SDL.h>

#include "Knight.h"
#include "Monster.h"
#include "Boss.h"
#include "SDL_utils.h"

using namespace std;

const int LEVEL_WIDTH = 2000;
const int LEVEL_HEIGHT = 400;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 480;

const int NUMBERS_OF_MONSTERS = 4;

void Game(SDL_Window* &window, SDL_Renderer* &renderer);
void Intro(SDL_Window* &window, SDL_Renderer* &renderer);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    init(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    Intro(window, renderer);
    //Game(window, renderer);
}

void Game(SDL_Window* &window, SDL_Renderer* &renderer)
{
    SDL_Rect SpriteCLips[12];
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    Sprite(SpriteCLips);

    SDL_Texture* mapp = load_bg(renderer, "map.png");

    Knight knight;
    knight.loadtexture("knight2.png", "knight1.png", renderer);
    knight.currentClip = &SpriteCLips[0];
    knight.render(0, 0, renderer, SpriteCLips);

    Monster monster[4];
    for(int i=0; i<=1; i++)
    {
        monster[i].path_left = "bigguy1.png";
        monster[i].path_right = "bigguy2.png";
        monster[i].loadtexture(renderer);
        monster[i].currentClip = &SpriteCLips[0];
        monster[i].render(0, 0, renderer);
    }

    for(int i=2; i<=3; i++)
    {
        monster[i].path_left = "monster1.png";
        monster[i].path_right = "monster2.png";
        monster[i].loadtexture(renderer);
        monster[i].currentClip = &SpriteCLips[0];
        monster[i].render(0, 0, renderer);
    }
    monster[0].mPosX = 900;
    monster[1].mPosX = 11900;
    monster[2].mPosX = 600;
    monster[3].mPosX = 11500;

    Boss boss;
    boss.loadtexture("boss2.png", "boss1.png", renderer);
    boss.currentClip = &SpriteCLips[0];
    boss.render(0, 0, renderer);

    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
            knight.stand_still(e);
        }
        knight.handleEvent(SpriteCLips, monster, boss, renderer, mapp, camera, LEVEL_WIDTH, LEVEL_HEIGHT);

        if(knight.mVelX == 0)
        {
            knight.currentClip = &SpriteCLips[knight.standing/20];
            knight.standing++;
            if(knight.standing/20 > 6) knight.standing = 100;
        }

        for(int i=0; i<=3; i++) monster[i].move(knight.mPosX, SpriteCLips);
        for(int i=0; i<=3; i++) knight.being_hit_status(monster[i], SpriteCLips);

        camera.x = knight.mPosX - SCREEN_WIDTH/2;
        camera.y = knight.mPosX - SCREEN_HEIGHT/2;

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

        if(boss.enter_boss_stage(knight.mPosX))
        {
            boss.move(knight.mPosX, SpriteCLips);
            camera.x = LEVEL_WIDTH - camera.w;
            camera.y = LEVEL_HEIGHT - camera.h;
            if(knight.mPosX <= 905) knight.mPosX+=5;
        }

        render_map(renderer, mapp, camera);
        knight.render(camera.x, camera.y, renderer, SpriteCLips);
        for(int i=0; i<=3; i++) monster[i].render(camera.x, camera.y, renderer);
        boss.render(camera.x, camera.y, renderer);
        SDL_RenderPresent(renderer);
    }
}

void Intro(SDL_Window* &window, SDL_Renderer* &renderer)
{
    SDL_Texture* ingame = load_bg(renderer, "knight1.png");
    SDL_Texture* button = load_bg(renderer, "playbutton.png");

    SDL_Rect SpriteButs[2];

    SpriteButs[0].x = 0;
    SpriteButs[0].y = 0;
    SpriteButs[0].w = 150;
    SpriteButs[0].h = 80;

    SpriteButs[1].x = 150;
    SpriteButs[1].y = 0;
    SpriteButs[1].w = 150;
    SpriteButs[1].h = 80;

    SDL_Rect currentButton = SpriteButs[0];

    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;

            if(e.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);

                bool inside = true;
                if(x < 450 || x > 550 || y < 200 || y > 300) inside = false;

                if(inside == true) currentButton = SpriteButs[1];
                else currentButton = SpriteButs[0];
            }

        }
        //SDL_RenderCopy(renderer, ingame, NULL, NULL);
        render_button(renderer, button, currentButton);
        SDL_RenderPresent(renderer);
    }
}

