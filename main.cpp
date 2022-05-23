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
void pause(SDL_Texture* pause_but, SDL_Renderer* renderer, SDL_Rect SpriteClips[]);

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
    SDL_Rect SpriteCLips[35];

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
    monster[0].mPosX = 1240;
    monster[1].mPosX = 2890;
    monster[2].mPosX = 3000;
    monster[3].mPosX = 4720;
    monster[4].mPosX = 4900;
    monster[5].mPosX = 870;
    monster[6].mPosX = 1650;
    monster[7].mPosX = 1700;
    monster[8].mPosX = 3200;
    monster[9].mPosX = 5000;

    Boss boss;
    boss.loadtexture("boss2.png", "boss1.png", renderer);
    boss.currentClip = &SpriteCLips[0];
    boss.render(0, 0, renderer, SpriteCLips);

    SDL_Texture* health = load_bg(renderer, "health.png");
    bool health_eaten = false;

    SDL_Texture* superslash_right = load_bg(renderer, "superslash1.png");
    SDL_Texture* superslash_left = load_bg(renderer, "superslash2.png");

    SDL_Texture* meteorite = load_bg(renderer, "meteorite.png");
    SDL_Texture* danger_sign = load_bg(renderer, "fuckingdanger.png");
    int meteo_frame = -350, rep = 0;

    SDL_Texture* pause_but = load_bg(renderer, "pause.png");
    SDL_Rect current = SpriteCLips[28];
    SDL_Rect quadrad = {10, 10, 50, 50};

    bool quit = false;
    bool inside;
    SDL_Event e;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
            knight.stand_still(e);

            if(e.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);

                inside = true;
                if(x<10 || x>50 || y<10 || y>50) inside = false;

                if(inside == true) current = SpriteCLips[29];
                else current = SpriteCLips[28];
            }

            if(inside == true && e.type == SDL_MOUSEBUTTONDOWN)
            {
                pause(pause_but, renderer, SpriteCLips);
            }
        }
        knight.handleEvent(SpriteCLips, monster, boss, renderer, mapp, health, superslash_left, superslash_right, camera, LEVEL_WIDTH, LEVEL_HEIGHT, rep, meteo_frame, danger_sign, meteorite);

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
            if(knight.mPosX >= 7100) knight.mPosX-=5;
        }

        if(knight.mPosX >= 5280 && health_eaten == false)//Health boost
        {
            SDL_DestroyTexture(health);
            if(knight.health.w <= 40) knight.health.w +=10;
            else knight.health.w = 50;
            health_eaten = true;
        }

        if(knight.currentClip != &SpriteCLips[4]) // Knight's falling
        {
            if(knight.mTexture == knight.right && ((knight.mPosX >= 2400 && knight.mPosX <= 2480) || (knight.mPosX >= 4150 && knight.mPosX <= 4230)))
            {
                if(knight.mPosX >= 2400 && knight.mPosX <= 2480) knight.mPosX = 2440;
                if(knight.mPosX >= 4150 && knight.mPosX <= 4230) knight.mPosX = 4190;

                while(knight.mPosY <= 700)
                {
                    knight.mPosY+=10;
                    SDL_RenderClear(renderer);
                    render_map(renderer, mapp, camera);
                    for(int i=0; i<=9; i++) monster[i].render(camera.x, camera.y, renderer);
                    knight.render(camera.x, camera.y, renderer, SpriteCLips);
                    SDL_RenderPresent(renderer);
                }
                return 0;
            }
            else if(knight.mTexture == knight.left && ((knight.mPosX >= 2370 && knight.mPosX <= 2450) || (knight.mPosX >= 4120 && knight.mPosX <= 4190)))
            {
                if(knight.mPosX >= 2370 && knight.mPosX <= 2450) knight.mPosX = 2410;
                if(knight.mPosX >= 4120 && knight.mPosX <= 4190) knight.mPosX = 4155;

                while(knight.mPosY <= 700)
                {
                    knight.mPosY+=10;
                    SDL_RenderClear(renderer);
                    render_map(renderer, mapp, camera);
                    for(int i=0; i<=9; i++) monster[i].render(camera.x, camera.y, renderer);
                    knight.render(camera.x, camera.y, renderer, SpriteCLips);
                    SDL_RenderPresent(renderer);
                }
                return 0;
            }
        }

        if(knight.health.w <= 0)
        {
            return 0;
        }
        if(boss.health.w <= 0)
        {
            return 1;
        }

        SDL_RenderClear(renderer);
        render_map(renderer, mapp, camera);
        render_items(renderer, health, camera.x);

        for(int i=0; i<=9; i++) monster[i].render(camera.x, camera.y, renderer);
        boss.render(camera.x, camera.y, renderer, SpriteCLips);

        knight.render(camera.x, camera.y, renderer, SpriteCLips);
        knight.slash_frame = render_super_slash(renderer, superslash_left, superslash_right, knight.slash_frame, knight.slash_distance, knight.direction, camera.x, monster, boss);

        rep = render_meteo(knight.mPosX, rep, meteo_frame, danger_sign, meteorite, renderer, camera.x, knight.health.w);
        SDL_RenderCopy(renderer, pause_but, &current, &quadrad);

        SDL_RenderPresent(renderer);
        //cout << knight.mPosX << endl;
    }
}

void Intro(SDL_Window* &window, SDL_Renderer* &renderer)
{
    SDL_Texture* ingamebg = load_bg(renderer, "introbg.png");
    SDL_Texture* play_button = load_bg(renderer, "playbutton.png");
    SDL_Texture* instruction_button = load_bg(renderer, "instructions.png");
    SDL_Texture* instruct_bg = load_bg(renderer, "instructionbg.png");
    SDL_Texture* backbutton = load_bg(renderer, "back.png");

    SDL_Rect SpriteButs[4];

    SpriteButs[0].x = 0;
    SpriteButs[0].y = 0;
    SpriteButs[0].w = 150;
    SpriteButs[0].h = 80;

    SpriteButs[1].x = 150;
    SpriteButs[1].y = 0;
    SpriteButs[1].w = 150;
    SpriteButs[1].h = 80;

    SpriteButs[2].x = 0;
    SpriteButs[2].y = 0;
    SpriteButs[2].w = 200;
    SpriteButs[2].h = 80;

    SpriteButs[3].x = 210;
    SpriteButs[3].y = 0;
    SpriteButs[3].w = 200;
    SpriteButs[3].h = 80;

    SDL_Rect currentButton = SpriteButs[0];
    SDL_Rect current_instruct = SpriteButs[2];
    SDL_Rect current_back = SpriteButs[0];

    bool start = false;
    bool instruct = false;
    bool inside_play, inside_instruct;
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

                inside_play = true;
                inside_instruct = true;

                if(x < 430 || x > 580 || y < 200 || y > 280)
                {
                    inside_play = false;
                }

                if(x < 425 || x > 575 || y < 300 || y > 380)
                {
                    inside_instruct = false;
                }

                if(inside_play == true) currentButton = SpriteButs[1];
                else currentButton = SpriteButs[0];

                if(inside_instruct == true) current_instruct = SpriteButs[3];
                else current_instruct = SpriteButs[2];
            }

            if(inside_play == true && e.type == SDL_MOUSEBUTTONDOWN) start = true;

            if(inside_instruct == true && e.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_Event eve;
                bool backk;
                bool undo = false;
                while(!undo)
                {
                    while(SDL_PollEvent(&eve) != 0)
                    {
                        if(eve.type == SDL_QUIT) undo = true;
                        if(eve.type == SDL_MOUSEMOTION)
                        {
                            int x, y;
                            SDL_GetMouseState(&x, &y);
                            backk = true;
                            if(x < 10 || x > 160 || y < 10 || y > 80)
                            {
                                backk = false;
                            }

                            if(backk == false) current_back = SpriteButs[0];
                            else current_back = SpriteButs[1];
                        }
                        if(backk == true && eve.type == SDL_MOUSEBUTTONDOWN) undo = true;
                    }

                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, instruct_bg, NULL, NULL);
                    back_button(renderer, backbutton, current_back);
                    SDL_RenderPresent(renderer);
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, ingamebg, NULL, NULL);
        render_button(renderer, play_button, instruction_button, currentButton,  current_instruct);
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

                if(x < 425 || x > 575 || y < 300 || y > 380)
                {
                    inside_quit = false;
                }

                if(inside_pa == true) current_pab = SpriteButs[1];
                else current_pab = SpriteButs[0];

                if(inside_quit == true) current_gob = SpriteButs[1];
                else current_gob = SpriteButs[0];
            }

            if(inside_pa == true && e.type == SDL_MOUSEBUTTONDOWN)
            {
                return true;
            }
            else if(inside_quit == true && e.type == SDL_MOUSEBUTTONDOWN)
            {
                return false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, game_over_bg, NULL, NULL);
        render_button(renderer, play_again_button, quit_button, current_pab, current_gob);
        SDL_RenderPresent(renderer);
    }
}

void pause(SDL_Texture* pause_but, SDL_Renderer* renderer, SDL_Rect SpriteClips[])
{
    SDL_Rect quadrad = {10, 10 , 50, 50};
    SDL_Rect current = SpriteClips[30];

    bool inside;
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
                inside = true;

                if(x < 10 || x > 50 || y < 10 || y > 50) inside = false;

                if(inside == true) current = SpriteClips[31];
                else current = SpriteClips[30];
            }
            if(inside == true && e.type == SDL_MOUSEBUTTONDOWN)
            {
                quit = true;
            }
        }
        SDL_RenderCopy(renderer, pause_but, &current, &quadrad);
        SDL_RenderPresent(renderer);
    }
}
