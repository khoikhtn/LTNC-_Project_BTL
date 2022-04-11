#include<iostream>
#include<SDL.h>

#include "Knight.h"
#include "Monster.h"
#include "SDL_utils.h"

using namespace std;

const int LEVEL_WIDTH = 2000;
const int LEVEL_HEIGHT = 400;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    init(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Rect SpriteCLips[6];
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    Sprite(SpriteCLips);

    SDL_Texture* mapp = load_map(renderer, "map.png");

    Knight knight;
    knight.loadtexture("knight2.png", "knight1.png", renderer);
    knight.currentClip = &SpriteCLips[0];
    knight.render(0, 0, renderer);

    Monster monster;
    monster.loadtexture("monster2.png", "monster1.png", renderer);
    monster.currentClip = &SpriteCLips[0];
    monster.render(0, 0, renderer);

    bool quit = false;
    SDL_Event e;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
            knight.handleEvent(e, SpriteCLips, monster, renderer, mapp, camera);
            knight.move();
        }
        monster.move(knight, SpriteCLips);

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

        if(e.key.keysym.sym != SDLK_z) SDL_RenderClear(renderer);
        render_map(renderer, mapp, camera);
        knight.render(camera.x, camera.y, renderer);
        monster.render(camera.x, camera.y, renderer);
        SDL_RenderPresent(renderer);
    }
}



