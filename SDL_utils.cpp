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

    SpriteClips[5].x = 1001;//Knight's standing
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
