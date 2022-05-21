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

    SpriteClips[14].x = 2101;//Super attack
    SpriteClips[14].y = 0;
    SpriteClips[14].w = 199;
    SpriteClips[14].h = 262;

    SpriteClips[15].x = 2301;
    SpriteClips[15].y = 0;
    SpriteClips[15].w = 199;
    SpriteClips[15].h = 262;

    SpriteClips[16].x = 2501;
    SpriteClips[16].y = 0;
    SpriteClips[16].w = 299;
    SpriteClips[16].h = 262;

    SpriteClips[17].x = 1801;//Rage boss
    SpriteClips[17].y = 0;
    SpriteClips[17].w = 199;
    SpriteClips[17].h = 262;

    SpriteClips[18].x = 2001;
    SpriteClips[18].y = 0;
    SpriteClips[18].w = 199;
    SpriteClips[18].h = 262;

    SpriteClips[19].x = 2201;
    SpriteClips[19].y = 0;
    SpriteClips[19].w = 249;
    SpriteClips[19].h = 262;

    SpriteClips[20].x = 1;//Smash ground
    SpriteClips[20].y = 263;
    SpriteClips[20].w = 940;
    SpriteClips[20].h = 261;

    SpriteClips[21].x = 1;
    SpriteClips[21].y = 525;
    SpriteClips[21].w = 940;
    SpriteClips[21].h = 261;

    SpriteClips[22].x = 1;
    SpriteClips[22].y = 787;
    SpriteClips[22].w = 940;
    SpriteClips[22].h = 261;

    SpriteClips[23].x = 1;
    SpriteClips[23].y = 1049;
    SpriteClips[23].w = 940;
    SpriteClips[23].h = 261;

    SpriteClips[24].x = 1;
    SpriteClips[24].y = 1311;
    SpriteClips[24].w = 940;
    SpriteClips[24].h = 261;

    SpriteClips[25].x = 1;
    SpriteClips[25].y = 1573;
    SpriteClips[25].w = 940;
    SpriteClips[25].h = 261;

    SpriteClips[26].x = 1;
    SpriteClips[26].y = 1835;
    SpriteClips[26].w = 940;
    SpriteClips[26].h = 261;

    SpriteClips[27].x = 1;
    SpriteClips[27].y = 2097;
    SpriteClips[27].w = 940;
    SpriteClips[27].h = 261;
}

SDL_Texture* load_bg(SDL_Renderer* renderer, string path)
{
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_Texture* mapp = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return mapp;
}

void render_map(SDL_Renderer* renderer, SDL_Texture* mapp, SDL_Rect camera)
{
    SDL_Rect quadrad = {0, 0, camera.w, camera.h};
    SDL_RenderCopy(renderer, mapp, &camera, &quadrad);
}

void render_button(SDL_Renderer* renderer, SDL_Texture* button1, SDL_Texture* button2, SDL_Rect currentButton1, SDL_Rect currentButton2)
{
    SDL_Rect quadrad1 = {430, 200, 150, 80};
    SDL_RenderCopy(renderer, button1, &currentButton1, &quadrad1);

    SDL_Rect quadrad2 = {400, 300, 200, 80};
    SDL_RenderCopy(renderer, button2, &currentButton2, &quadrad2);
}

int render_super_slash(SDL_Renderer* renderer, SDL_Texture* superslash_l, SDL_Texture* superslash_r, int frame, int dis, bool direction, int camX, Monster monster[])
{
    if(direction == false)
    {
        SDL_Rect quadrad = {frame - 300 - camX, 200, 251, 262};
        SDL_RenderCopy(renderer, superslash_l, NULL, &quadrad);
        frame-=4;
        for(int i=0; i<=9; i++)
        {
            if(quadrad.x - monster[i].mPosX + camX  >= 0 && quadrad.x - monster[i].mPosX +camX <= 5)
            {
                if(monster[i].health.w >= 10) monster[i].health.w-=10;
                else monster[i].health.w = 0;
            }
        }
        if(abs(frame - dis) >= 500) frame = -100;
    }
    else
    {
        SDL_Rect quadrad = {frame - 150 - camX, 200, 251, 262};
        SDL_RenderCopy(renderer, superslash_r, NULL, &quadrad);
        frame+=4;
        for(int i=0; i<=9; i++)
        {
            if(monster[i].mPosX - quadrad.x - camX - 80 >= 0 && monster[i].mPosX - quadrad.x - camX - 80 <= 5)
            {
                if(monster[i].health.w >= 10) monster[i].health.w-=10;
                else monster[i].health.w = 0;
            }
        }
        if(abs(frame - dis) >= 500) frame = 10000;
    }

    return frame;
}

void render_items(SDL_Renderer* renderer, SDL_Texture* item, int camX)
{
    SDL_Rect quadrad = {900 - camX, 330, 80, 50};
    SDL_RenderCopy(renderer, item, NULL, &quadrad);
}

void back_button(SDL_Renderer* renderer, SDL_Texture* backbut, SDL_Rect current_back)
{
    SDL_Rect quadrad = {10, 10, 150, 80};
    SDL_RenderCopy(renderer, backbut, &current_back, &quadrad);
}
