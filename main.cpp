#include<iostream>
#include<SDL.h>

#include "Knight.h"
#include "Monster.h"
#include "Boss.h"
#include "SDL_utils.h"

using namespace std;

const int LEVEL_WIDTH = 7230;
const int LEVEL_HEIGHT = 400;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 480;

const int NUMBERS_OF_MONSTERS = 4;

void Intro(SDL_Window* &window, SDL_Renderer* &renderer);
int Game(SDL_Window* &window, SDL_Renderer* &renderer);
bool play_again(SDL_Window* &window, SDL_Renderer* &renderer, int k);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    init(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    Intro(window, renderer);
    while(true)
    {
        int k = Game(window, renderer);
        if( play_again(window, renderer, k)) continue;
        else break;
    }
    quitSDL(window, renderer);
    }

int Game(SDL_Window* &window, SDL_Renderer* &renderer)
{
    SDL_Rect SpriteCLips[20];
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    Sprite(SpriteCLips);

    SDL_Texture* mapp = load_bg(renderer, "background.jpg");

    Knight knight;
    knight.loadtexture("knight2.png", "knight1.png", renderer);
    knight.currentClip = &SpriteCLips[0];
    knight.render(0, 0, renderer, SpriteCLips);

    Monster monster[10];
    for(int i=0; i<=4; i++)
    {
        monster[i].path_left = "bigguy1.png";
        monster[i].path_right = "bigguy2.png";
        monster[i].loadtexture(renderer);
        monster[i].currentClip = &SpriteCLips[0];
        monster[i].render(0, 0, renderer);
    }

    for(int i=5; i<=9; i++)
    {
        monster[i].path_left = "monster1.png";
        monster[i].path_right = "monster2.png";
        monster[i].loadtexture(renderer);
        monster[i].currentClip = &SpriteCLips[0];
        monster[i].render(0, 0, renderer);
    }
    monster[0].mPosX = ;
    monster[1].mPosX = ;
    monster[2].mPosX = ;
    monster[3].mPosX = ;
    monster[4].mPosX = ;
    monster[5].mPosX = ;
    monster[6].mPosX = ;
    monster[7].mPosX = ;
    monster[8].mPosX = ;
    monster[9].mPosX = ;

    Boss boss;
    boss.loadtexture("boss2.png", "boss1.png", renderer);
    boss.currentClip = &SpriteCLips[0];
    boss.render(0, 0, renderer);

    SDL_Texture* health = load_bg(renderer, "health.png");
    bool health_eaten = false;

    SDL_Texture* superslash_right = load_bg(renderer, "superslash1.png");
    SDL_Texture* superslash_left = load_bg(renderer, "superslash2.png");

    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
            knight.stand_still(e);
        }
        knight.handleEvent(SpriteCLips, monster, boss, renderer, mapp, health, superslash_left, superslash_right, camera, LEVEL_WIDTH, LEVEL_HEIGHT);

        if(knight.mVelX == 0)// Knight's standstill
        {
            knight.currentClip = &SpriteCLips[knight.standing/20];
            knight.standing++;
            if(knight.standing/20 > 6) knight.standing = 100;
        }

        for(int i=0; i<=9; i++) monster[i].move(knight.mPosX, SpriteCLips);
        for(int i=0; i<=9; i++) knight.being_hit_status(monster[i], SpriteCLips);
        knight.being_hit_by_boss_status(boss, SpriteCLips);

        camera.x = knight.mPosX - SCREEN_WIDTH/2;
        camera.y = knight.mPosY - SCREEN_HEIGHT/2;

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

        if(boss.enter_boss_stage(knight.mPosX))//Enter boss stage
        {
            if(knight.mPosX <= 5410) knight.mPosX = 6175;
            boss.move(knight.mPosX, SpriteCLips);
            camera.x = LEVEL_WIDTH - camera.w;
            camera.y = LEVEL_HEIGHT - camera.h;
            if(knight.mPosX <= 6170) knight.mPosX+=5;
        }

        if(knight.mPosX >= 850 && knight.mPosX <= 1200 && health_eaten == false)//Health boost
        {
            SDL_DestroyTexture(health);
            if(knight.health.w <= 40) knight.health.w +=10;
            else knight.health.w = 50;
            health_eaten = true;
        }

        if(knight.health.w == 0)
        {
            return 0;
        }
        if(boss.health.w == 0)
        {
            return 1;
        }

        SDL_RenderClear(renderer);
        render_map(renderer, mapp, camera);
        render_items(renderer, health, camera.x);
        knight.render(camera.x, camera.y, renderer, SpriteCLips);
        knight.slash_frame = render_super_slash(renderer, superslash_left, superslash_right, knight.slash_frame, knight.slash_distance, knight.direction, camera.x, monster);
        for(int i=0; i<=9; i++) monster[i].render(camera.x, camera.y, renderer);
        boss.render(camera.x, camera.y, renderer);

        SDL_RenderPresent(renderer);
    }
}

void Intro(SDL_Window* &window, SDL_Renderer* &renderer)
{
    SDL_Texture* ingamebg = load_bg(renderer, "introbg.png");
    SDL_Texture* play_button = load_bg(renderer, "playbutton.png");

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

    bool start = false;
    bool inside;
    bool quit = false;
    SDL_Event e;
    while(!quit && !start)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;

            if(e.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                inside = true;
                if(x < 430 || x > 580 || y < 200 || y > 280)
                {
                    inside = false;
                }

                if(inside == true) currentButton = SpriteButs[1];
                else currentButton = SpriteButs[0];
            }
        }
        if(inside == true && e.type == SDL_MOUSEBUTTONDOWN) start = true;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, ingamebg, NULL, NULL);
        render_start_button(renderer, play_button, currentButton);
        SDL_RenderPresent(renderer);
    }
}

bool play_again(SDL_Window* &window, SDL_Renderer* &renderer, int k)
{
    SDL_Texture* game_over_bg;
    if(k == 0) game_over_bg = load_bg(renderer, "gobg.png");
    else if(k == 1) game_over_bg = load_bg(renderer, "victorybg.png");
    SDL_Texture* play_again_button = load_bg(renderer, "pabt.png");
    SDL_Texture* quit_button = load_bg(renderer, "qb.png");

    SDL_Rect SpriteButs[2];

    SpriteButs[0].x = 0;
    SpriteButs[0].y = 0;
    SpriteButs[0].w = 150;
    SpriteButs[0].h = 80;

    SpriteButs[1].x = 150;
    SpriteButs[1].y = 0;
    SpriteButs[1].w = 150;
    SpriteButs[1].h = 80;

    SDL_Rect current_pab = SpriteButs[0];
    SDL_Rect current_gob = SpriteButs[0];

    bool inside_pa, inside_quit;
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
                inside_pa = true;
                inside_quit = true;

                if(x < 430 || x > 580 || y < 200 || y > 280)
                {
                    inside_pa = false;
                }

                if(x < 430 || x > 580 || y < 300 || y > 380)
                {
                    inside_quit = false;
                }

                if(inside_pa == true) current_pab = SpriteButs[1];
                else current_pab = SpriteButs[0];

                if(inside_quit == true) current_gob = SpriteButs[1];
                else current_gob = SpriteButs[0];
            }
        }
        if(inside_pa == true && e.type == SDL_MOUSEBUTTONDOWN)
        {
            return true;
        }
        else if(inside_quit == true && e.type == SDL_MOUSEBUTTONDOWN)
        {
            return false;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, game_over_bg, NULL, NULL);
        render_play_again_button(renderer, play_again_button, quit_button, current_pab, current_gob);
        SDL_RenderPresent(renderer);
    }
}

