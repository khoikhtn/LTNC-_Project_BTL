#include "SDL_utils.h"

void init(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    window = SDL_CreateWindow("A Knight's Tale", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Sprite(SDL_Rect SpriteClips[])
{
    SpriteClips[0].x = 0;
    SpriteClips[0].y = 0;
    SpriteClips[0].w = 199;
    SpriteClips[0].h = 262;

    SpriteClips[1].x = 201;
    SpriteClips[1].y = 0;
    SpriteClips[1].w = 199;
    SpriteClips[1].h = 262;

    SpriteClips[2].x = 401;
    SpriteClips[2].y = 0;
    SpriteClips[2].w = 199;
    SpriteClips[2].h = 262;

    SpriteClips[3].x = 601;
    SpriteClips[3].y = 0;
    SpriteClips[3].w = 199;
    SpriteClips[3].h = 262;

    SpriteClips[4].x = 801;//Knight's jump
    SpriteClips[4].y = 0;
    SpriteClips[4].w = 199;
    SpriteClips[4].h = 262;

    SpriteClips[5].x = 1001;//Knight's stand still
    SpriteClips[5].y = 0;
    SpriteClips[5].w = 199;
    SpriteClips[5].h = 262;

    SpriteClips[6].x = 1201;
    SpriteClips[6].y = 0;
    SpriteClips[6].w = 199;
    SpriteClips[6].h = 262;

    SpriteClips[7].x = 1401;//Knight's attack
    SpriteClips[7].y = 0;
    SpriteClips[7].w = 199;
    SpriteClips[7].h = 262;

    SpriteClips[8].x = 1601;
    SpriteClips[8].y = 0;
    SpriteClips[8].w = 299;
    SpriteClips[8].h = 262;

    SpriteClips[9].x = 1001; //Boss's launching
    SpriteClips[9].y = 0;
    SpriteClips[9].w = 329;
    SpriteClips[9].h = 262;

    SpriteClips[10].x = 1901; //Knight's Sliding
    SpriteClips[10].y = 0;
    SpriteClips[10].w = 199;
    SpriteClips[10].h = 262;

    SpriteClips[11].x = 1401; //Monster's stand still and Boss's stunt
    SpriteClips[11].y = 0;
    SpriteClips[11].w = 199;
    SpriteClips[11].h = 262;

    SpriteClips[12].x = 1601;
    SpriteClips[12].y = 0;
    SpriteClips[12].w = 199;
    SpriteClips[12].h = 262;

    SpriteClips[13].x = 0;//Empty Space
    SpriteClips[13].y = 0;
    SpriteClips[13].w = 1;
    SpriteClips[13].h = 1;

}

SDL_Texture* load_bg(SDL_Renderer* renderer, string path)
{
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    SDL_Texture* mapp = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return mapp;
}

void render_map(SDL_Renderer* renderer, SDL_Texture* mapp, SDL_Rect camera)
{
    SDL_Rect quadrad = {0, 0, camera.w, camera.h};
    SDL_RenderCopy(renderer, mapp, &camera, &quadrad);
}

void render_start_button(SDL_Renderer* renderer, SDL_Texture* button, SDL_Rect currentButton)
{
    SDL_Rect quadrad = {430, 200, 150, 80};
    SDL_RenderCopy(renderer, button, &currentButton, &quadrad);
}

void render_play_again_button(SDL_Renderer* renderer, SDL_Texture* button1, SDL_Texture* button2, SDL_Rect currentButton1, SDL_Rect currentButton2)
{
    SDL_Rect quadrad1 = {430, 200, 150, 80};
    SDL_RenderCopy(renderer, button1, &currentButton1, &quadrad1);

    SDL_Rect quadrad2 = {430, 300, 150, 80};
    SDL_RenderCopy(renderer, button2, &currentButton2, &quadrad2);
}

void render_items(SDL_Renderer* renderer, SDL_Texture* item, int camX)
{
    SDL_Rect quadrad = {900 - camX, 330, 80, 50};
    SDL_RenderCopy(renderer, item, NULL, &quadrad);
}
