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

const int NUMBERS_OF_MONSTERS = 4;
int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    init(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Rect SpriteCLips[10];
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    Sprite(SpriteCLips);

    SDL_Texture* mapp = load_map(renderer, "map.png");

    Knight knight;
    knight.loadtexture("knight2.png", "knight1.png", renderer);
    knight.currentClip = &SpriteCLips[0];
    knight.render(0, 0, renderer, SpriteCLips);

    Monster monster[4];
    for(int i=0; i<=3; i++)
    {
        monster[i].path_left = "bigguy1.png";
        monster[i].path_right = "bigguy2.png";
        monster[i].loadtexture(renderer);
        monster[i].currentClip = &SpriteCLips[0];
        monster[i].render(0, 0, renderer);
    }
    monster[1].mPosX = 800;
    //monster[2].mPosX = 700;
    //monster[3].mPosX = 900;

    bool quit = false;
    SDL_Event e;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
            knight.handleEvent(e, SpriteCLips, monster, renderer, mapp, camera, LEVEL_WIDTH, LEVEL_HEIGHT);
            knight.move(e, SpriteCLips);
        }
        if(knight.mVelX==0)
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

        render_map(renderer, mapp, camera);
        knight.render(camera.x, camera.y, renderer, SpriteCLips);
        for(int i=0; i<=3; i++) monster[i].render(camera.x, camera.y, renderer);
        SDL_RenderPresent(renderer);
    }
}


/*#include <iostream>
#include <SDL.h>
#include<SDL_image.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

void initSDL();
class cacon;
class ca{
    public:
        void load_anh(string path);
        void handle_event(SDL_Event &e, SDL_Rect SpriteClips[]);
        void move(SDL_Event &e,cacon camini, SDL_Rect SpriteClips[]);
        void render_ca();
        bool check_collision(cacon camini);
        int toadox=0;
        int toadoy=0;
        int velx=0, vely=0;
        SDL_Rect *current_clip;
        int frame =0;

        SDL_Texture *concadan;
};

class cacon{
    public:
        int toadox = SCREEN_WIDTH/2 , toadoy = SCREEN_HEIGHT/2;
        int frame =0;
        int speed = 0;
        SDL_Rect* current_clip;
        SDL_Texture* mTexture;
        void load_anh(string path);
        void move(bool direction);
        void render();
};
bool ca::check_collision(cacon camini){
    if(toadox + current_clip.w == camini.toadox) return true;
    return false;
}
void cacon::load_anh(string path)
{
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(loadedSurface,SDL_TRUE, SDL_MapRGB(loadedSurface->format,0xFF,0xFF,0xFF));
    mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
}

void cacon::move(bool direction)
{
    if(direction){
        toadox++;
    }
    else{
        toadox--;
    }
}

void cacon::render()
{
    SDL_Rect quadrad = {toadox, toadoy, current_clip->w, current_clip->h};
    SDL_RenderCopy(gRenderer, mTexture, current_clip, &quadrad);
}

void ca::load_anh(string path){
    SDL_Surface *loadsurface = IMG_Load(path.c_str());
    SDL_SetColorKey(loadsurface,SDL_TRUE, SDL_MapRGB(loadsurface->format,0xFF,0xFF,0xFF));
    concadan = SDL_CreateTextureFromSurface(gRenderer,loadsurface);
}
void ca::move(SDL_Event &e, cacon camini, SDL_Rect SpriteClips[]){
    if(e.type == SDL_MOUSEMOTION);
    else{
    toadox += velx;
    toadoy += vely;}
   if(check_collision(camini)){
        camini.current_clip = &SpriteClips[6];
    }
}
void ca::render_ca(){
    SDL_Rect toadoca = {toadox,toadoy,current_clip->w, current_clip->h};
    SDL_RenderCopy(gRenderer, concadan,current_clip, &toadoca);
}
void ca::handle_event(SDL_Event &e, SDL_Rect SpriteClips[]){
    if(e.type==SDL_KEYDOWN && e.key.repeat==0){
        switch(e.key.keysym.sym) {
            case SDLK_RIGHT : velx++; break;
            case SDLK_LEFT : velx--; break;
            case SDLK_UP : vely--; break;
            case SDLK_DOWN : vely ++; break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat==0){
        switch(e.key.keysym.sym) {
            case SDLK_RIGHT : velx--; break;
            case SDLK_LEFT : velx++; break;
            case SDLK_UP : vely++; break;
            case SDLK_DOWN : vely --; break;
        }
    }
    if(e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT){
        current_clip = &SpriteClips[frame/3];
        frame++;
        if(frame == 9) frame =0;
    }
    if(e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN){
        current_clip = &SpriteClips[frame/3];
        frame++;
        if(frame == 9) frame =0;
    }
}

void loadBackground(){
    SDL_Surface *loadsurface = IMG_Load("backgroundocean.jpg");
    SDL_Texture *background = SDL_CreateTextureFromSurface(gRenderer,loadsurface);
    SDL_RenderCopy(gRenderer,background,nullptr,nullptr);
}
void initSDL()
{
    gWindow = SDL_CreateWindow("Big_game_test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
}
int main(int argc, char* argv[])
{
    initSDL();
    bool quit = false;
    SDL_Event e;
    SDL_Rect SpriteClips[9];
    SpriteClips[0].x = 0;
    SpriteClips[0].y=0;
    SpriteClips[0].w = 264;
    SpriteClips[0].h = 161;
    SpriteClips[1].x = 264;
    SpriteClips[1].y=0;
    SpriteClips[1].w = 256;
    SpriteClips[1].h = 161;
    SpriteClips[2].x = 520;
    SpriteClips[2].y = 0;
    SpriteClips[2].w = 280;
    SpriteClips[2].h = 161;

    SpriteClips[3].x = 0;
    SpriteClips[3].y = 0;
    SpriteClips[3].w = 150;
    SpriteClips[3].h = 205;

    SpriteClips[4].x = 152;
    SpriteClips[4].y = 0;
    SpriteClips[4].w = 150;
    SpriteClips[4].h = 205;

    SpriteClips[5].x = 300;
    SpriteClips[5].y = 0;
    SpriteClips[5].w = 150;
    SpriteClips[5].h = 205;

    SpriteClips[6].x = 0;
    SpriteClips[6].y = 0;
    SpriteClips[6].w = 1;
    SpriteClips[6].h = 1;
    bool direction = false;
    ca conca;
    cacon camini;
    srand(time(0));
    int r = rand()%2;
    if(r == 0) direction = true;

    conca.load_anh("sharkthangrmbg.png");
    conca.current_clip = &SpriteClips[0];

    camini.load_anh("cadichuyen.png");
    camini.current_clip = &SpriteClips[3];

    while(!quit){
        while(SDL_PollEvent(&e)!=0){
            if(e.type == SDL_QUIT)  quit = true;
            conca.handle_event(e, SpriteClips);
            conca.move(e,camini,SpriteClips);
        }
        //camini.move(direction);
        SDL_RenderClear(gRenderer);
        loadBackground();
        camini.render();
        conca.render_ca();
        SDL_RenderPresent(gRenderer);
    }
}*/
