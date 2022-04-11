#include "SDL_utils.h"

void init(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    window = SDL_CreateWindow("Big_game_test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
    SpriteClips[0].w = 90;
    SpriteClips[0].h = 208;

    SpriteClips[1].x = 90;
    SpriteClips[1].y = 0;
    SpriteClips[1].w = 90;
    SpriteClips[1].h = 208;

    SpriteClips[2].x = 180;
    SpriteClips[2].y = 0;
    SpriteClips[2].w = 90;
    SpriteClips[2].h = 208;

    SpriteClips[3].x = 270;
    SpriteClips[3].y = 0;
    SpriteClips[3].w = 90;
    SpriteClips[3].h = 208;

    SpriteClips[4].x = 360;
    SpriteClips[4].y = 0;
    SpriteClips[4].w = 90;
    SpriteClips[4].h = 208;

    SpriteClips[5].x = 450;
    SpriteClips[5].y = 0;
    SpriteClips[5].w = 90;
    SpriteClips[5].h = 208;
}

SDL_Texture* load_map(SDL_Renderer* renderer, string path)
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
