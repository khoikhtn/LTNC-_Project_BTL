#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
using namespace std;

const int LEVEL_WIDTH = 2000;
const int LEVEL_HEIGHT = 400;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Rect gSpriteClips[8];

class LTexture
{
    public:
        void loadFromFile(string path);
        void render(int x, int y, SDL_Rect* clip = NULL);
    private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
};

class knight
{
	public:
		void handleEvent(SDL_Event &e);
		void move();
		void render(int camX, int camY);
		SDL_Rect* currentClip = &gSpriteClips[0];
		SDL_Rect health = {0, 0, 50, 10};
		int frame = 0;
	//private:
		int mPosX, mPosY;
		int mVelX, mVelY;
};

class monster
{
    public:
        void move();
        void render(int camX, int camY);
        SDL_Rect* currentClip;
        SDL_Rect health = {0, 0, 30, 10};
        int frame = 0, fight_scene = 300;
        int mPosX, mPosY;
};

void init();
void loadMedia();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;


LTexture gBGTexture;
LTexture gKnight1;
LTexture gKnight2;
LTexture gKnight;
LTexture gMonster1;
LTexture gMonster2;
LTexture gMonster;

SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

knight Knight;
monster Monster;

void init()
{
    gWindow = SDL_CreateWindow("Big_game_test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
}

void loadMedia()
{
    gBGTexture.loadFromFile("map.png");
    gKnight2.loadFromFile("knight2.png");
    gKnight1.loadFromFile("knight.png");
    gMonster1.loadFromFile("monster1.png");
    gMonster2.loadFromFile("monster2.png");
    gSpriteClips[0].x = 0;
    gSpriteClips[0].y = 0;
    gSpriteClips[0].w = 64;
    gSpriteClips[0].h = 205;

    gSpriteClips[1].x = 64;
    gSpriteClips[1].y = 0;
    gSpriteClips[1].w = 64;
    gSpriteClips[1].h = 205;

    gSpriteClips[2].x = 128;
    gSpriteClips[2].y = 0;
    gSpriteClips[2].w = 64;
    gSpriteClips[2].h = 205;

    gSpriteClips[3].x = 192;
    gSpriteClips[3].y = 0;
    gSpriteClips[3].w = 64;
    gSpriteClips[3].h = 205;

    gSpriteClips[4].x = 256;//Knight fight scene
    gSpriteClips[4].y = 0;
    gSpriteClips[4].w = 144;
    gSpriteClips[4].h = 205;

    gSpriteClips[5].x = 400;
    gSpriteClips[5].y = 0;
    gSpriteClips[5].w = 191;
    gSpriteClips[5].h = 205;

    gSpriteClips[6].x = 256;//Monster fight scene
    gSpriteClips[6].y = 0;
    gSpriteClips[6].w = 88;
    gSpriteClips[6].h = 205;

    gSpriteClips[7].x = 355;
    gSpriteClips[7].y = 0;
    gSpriteClips[7].w = 75;
    gSpriteClips[7].h = 205;
}

void LTexture::render(int x, int y, SDL_Rect* clip)
{
    SDL_Rect quadrad = {x, y, mWidth, mHeight};
    if(clip!= NULL)
    {
        quadrad.w = clip->w;
        quadrad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &quadrad);
}

void LTexture::loadFromFile(string path)
{
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
    mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
}

void knight::handleEvent (SDL_Event &e)
{
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch(e.key.keysym.sym)
		{
			case SDLK_RIGHT: mVelX++; gKnight = gKnight2; break;
			case SDLK_LEFT: mVelX--; gKnight = gKnight1; break;
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
    if(e.key.keysym.sym == SDLK_RIGHT)
    {
    	SDL_RenderClear(gRenderer);
        currentClip = &gSpriteClips[frame/4];
        frame--;
        if(frame/4 <= -1) frame = 15;
    }

    else if(e.key.keysym.sym == SDLK_LEFT)
    {
        SDL_RenderClear(gRenderer);
        currentClip = &gSpriteClips[frame/4];
        frame++;
        if(frame/4 >=4) frame = 0;
    }

    if(e.key.keysym.sym == SDLK_z && e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        int fight_scene = 40;
        while(fight_scene/10 <=5)
        {
            currentClip = &gSpriteClips[fight_scene/10];
            SDL_RenderClear(gRenderer);
            gBGTexture.render(0, 0, &camera);
            gKnight.render(mPosX-camera.x, mPosY-camera.y, currentClip);
            if(Monster.mPosX > mPosX)
            {
                if(Monster.mPosX - mPosX <= 400 && Monster.mPosX - mPosX >=50)
                {
                    Monster.mPosX--;
                    Monster.currentClip = &gSpriteClips[Monster.frame/4];
                    Monster.frame++;
                    if(Monster.frame/4 >= 4) Monster.frame = 0;
                }

                if(Monster.mPosX - mPosX < 50)
                {
                    Monster.currentClip = &gSpriteClips[Monster.fight_scene/50];
                    Monster.fight_scene++;
                    if(Monster.fight_scene/50 >= 8) Monster.fight_scene = 300;
                }
            }

            else
            {
                if(mPosX - Monster.mPosX >= 70 && mPosX - Monster.mPosX <= 400)
                {
                    Monster.mPosX++;
                    Monster.currentClip = &gSpriteClips[Monster.frame/4];
                    Monster.frame++;
                    if(Monster.frame/4 >= 4) Monster.frame = 0;
                }
                if(mPosX - Monster.mPosX < 70)
                {
                    Monster.currentClip = &gSpriteClips[Monster.fight_scene/50];
                    Monster.fight_scene++;
                    if(Monster.fight_scene/50 >= 8) Monster.fight_scene = 300;
                }
            }
            gMonster.render(Monster.mPosX - camera.x, Monster.mPosY, Monster.currentClip);
            SDL_RenderPresent(gRenderer);
            fight_scene++;
        }
        SDL_Delay(100);
        SDL_RenderClear(gRenderer);
        currentClip = &gSpriteClips[frame/4];
    }
}

void knight::move()
{
	mPosX += mVelX*3;
	if(mPosX < 0) mPosX -= mVelX*3;
}

void knight::render(int camX, int camY)
{
    health.x = mPosX - health.w/2 + currentClip->w/2 - camera.x;
    health.y = mPosY + 60;
    SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
    SDL_RenderFillRect(gRenderer, &health);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    gKnight.render(mPosX - camX, mPosY - camY, currentClip);
}

void monster::move()
{
    if(Knight.mPosX < mPosX)
    {
        gMonster = gMonster1;
        if(mPosX - Knight.mPosX <= 400 && mPosX - Knight.mPosX >= 50)
        {
            mPosX--;
            currentClip = &gSpriteClips[frame/4];
            frame++;
            if(frame/4 >= 4) frame = 0;
        }
        if(mPosX - Knight.mPosX < 50)
        {
            currentClip = &gSpriteClips[fight_scene/50];
            fight_scene++;
            if(fight_scene/50 >= 8) fight_scene = 300;
        }
    }

    else
    {
        gMonster = gMonster2;
        if(Knight.mPosX - mPosX >= 70 && Knight.mPosX - mPosX <= 400)
        {
            mPosX++;
            currentClip = &gSpriteClips[frame/4];
            frame++;
            if(frame/4 >= 4) frame = 0;
        }
        if(Knight.mPosX - mPosX < 70)
        {
            currentClip = &gSpriteClips[fight_scene/50];
            fight_scene++;
            if(fight_scene/50 >= 8) fight_scene = 300;
        }
    }
}

void monster::render(int camX, int camY)
{
    health.x = mPosX - health.w/2 + currentClip->w/2 - camera.x;
    health.y = mPosY + 60;
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(gRenderer, &health);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    gMonster.render(mPosX - camX, mPosY, currentClip);
}

/*bool check_hit()
{
	if(Monster.mPosX )
}*/

int main(int argc, char* argv[])
{
    init();
    loadMedia();
    bool quit = false;
    SDL_Event e;

    Knight.mPosX = 0;
    Knight.mPosY = 150;

    Monster.mPosX = 500;
    Monster.mPosY = 242;
    Monster.currentClip = &gSpriteClips[0];

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit = true;
            Knight.handleEvent(e);
            Knight.move();
        }
        Monster.move();
        camera.x = Knight.mPosX - SCREEN_WIDTH / 2;
        camera.y = Knight.mPosY - SCREEN_HEIGHT / 2;

        if( camera.x < 0 )
        {
            camera.x = 0;
        }
        if( camera.y < 0 )
        {
            camera.y = 0;
        }
        if( camera.x > LEVEL_WIDTH - camera.w )
        {
            camera.x = LEVEL_WIDTH - camera.w;
        }
        if( camera.y > LEVEL_HEIGHT - camera.h )
        {
            camera.y = LEVEL_HEIGHT - camera.h;
        }

        SDL_RenderClear(gRenderer);
        gBGTexture.render(0, 0, &camera);
        Knight.render(camera.x, camera.y);
        Monster.render(camera.x, camera.y);

        SDL_RenderPresent(gRenderer);
    }
}
