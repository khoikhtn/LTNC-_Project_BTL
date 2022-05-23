#include "Knight.h"

void Knight::loadtexture(string path_right, string path_left, SDL_Renderer* renderer)
{
    SDL_Surface* loadedSurface = IMG_Load(path_right.c_str());
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
    right = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    loadedSurface = IMG_Load(path_left.c_str());
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
    left = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    mTexture = right;

    SDL_FreeSurface(loadedSurface);

}

void Knight::handleEvent(SDL_Rect SpriteClips[], Monster monster[], Boss &boss, SDL_Renderer* renderer, SDL_Texture* mapp, SDL_Texture* item, SDL_Texture* superslash_left, SDL_Texture* superslash_right, SDL_Rect camera, int LEVEL_WIDTH, int LEVEL_HEIGHT, int &rep, int &meteo_frame, SDL_Texture* danger_sign, SDL_Texture* meteo)
{
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    //Left and Right
    if(keystates[SDL_SCANCODE_LEFT])
    {
        mPosX-=4;
        mTexture = left;
        currentClip = &SpriteClips[frame/10];
        frame++;
        if(frame/10 >= 4) frame = 0;
    }
    if(keystates[SDL_SCANCODE_RIGHT])
    {
        mPosX+=4;
        mTexture = right;
        currentClip = &SpriteClips[frame/10];
        frame++;
        if(frame/10 >= 4) frame = 0;
    }

    //Up: Jump
    if(keystates[SDL_SCANCODE_UP])
    {
        currentClip = &SpriteClips[4];
        int i=1;
        while(i<=11)
        {
            mPosY-=i;
            if(keystates[SDL_SCANCODE_RIGHT]) mPosX+=5;
            if(keystates[SDL_SCANCODE_LEFT]) mPosX-=5;
            for(int i=0; i<=9; i++) monster[i].move(mPosX, SpriteClips);
            camera.x = mPosX - camera.w/2;
            camera.y = mPosY - camera.h/2;
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

            if(boss.enter_boss_stage(mPosX))
            {
                if(mPosX <= 5410) mPosX = 6175;
                boss.move(mPosX, SpriteClips);
                camera.x = LEVEL_WIDTH - camera.w;
                camera.y = LEVEL_HEIGHT - camera.h;
                if(mPosX <= 6170) mPosX+=2;
            }

            SDL_RenderClear(renderer);
            render_map(renderer, mapp, camera);
            render_items(renderer, item, camera.x);

            for(int i=0; i<=9; i++) monster[i].render(camera.x, camera.y, renderer);
            boss.render(camera.x, camera.y, renderer, SpriteClips);

            this->render(camera.x, camera.y, renderer, SpriteClips);
            slash_frame = render_super_slash(renderer, superslash_left, superslash_right, slash_frame, slash_distance, direction, camera.x, monster, boss);

            rep = render_meteo(mPosX, rep, meteo_frame, danger_sign, meteo, renderer, camera.x, health.w);

            SDL_RenderPresent(renderer);
            i++;
        }
        i=1;
        while(i<=11)
        {
            mPosY+=i;
            if(keystates[SDL_SCANCODE_RIGHT]) mPosX+=5;
            if(keystates[SDL_SCANCODE_LEFT]) mPosX-=5;
            for(int i=0; i<=9; i++) monster[i].move(mPosX, SpriteClips);
            camera.x = mPosX - camera.w/2;
            camera.y = mPosY - camera.h/2;
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

            if(boss.enter_boss_stage(mPosX))
            {
                if(mPosX <= 5410) mPosX = 6175;
                boss.move(mPosX, SpriteClips);
                camera.x = LEVEL_WIDTH - camera.w;
                camera.y = LEVEL_HEIGHT - camera.h;
                if(mPosX <= 6170) mPosX+=2;
            }

            SDL_RenderClear(renderer);
            render_map(renderer, mapp, camera);
            render_items(renderer, item, camera.x);

            for(int i=0; i<=9; i++) monster[i].render(camera.x, camera.y, renderer);
            boss.render(camera.x, camera.y, renderer, SpriteClips);

            this->render(camera.x, camera.y, renderer, SpriteClips);
            slash_frame = render_super_slash(renderer, superslash_left, superslash_right, slash_frame, slash_distance, direction, camera.x, monster, boss);

            rep = render_meteo(mPosX, rep, meteo_frame, danger_sign, meteo, renderer, camera.x, health.w);

            SDL_RenderPresent(renderer);
            i++;
        }
    }

    //Z: Attack
    if(keystates[SDL_SCANCODE_Z])
    {
        int fight_scene = 70;
        while(fight_scene/10 <= 8)
        {
            currentClip = &SpriteClips[fight_scene/10];
            for(int i=0; i<=9; i++) monster[i].move(mPosX, SpriteClips);
            for(int i=0; i<=9; i++) this->hits_monster_status(monster[i], SpriteClips);
            this->hits_boss_status(boss, SpriteClips);

            if(boss.enter_boss_stage(mPosX))
            {
                if(mPosX <= 5410) mPosX = 6175;
                boss.move(mPosX, SpriteClips);
                camera.x = LEVEL_WIDTH - camera.w;
                camera.y = LEVEL_HEIGHT - camera.h;
                if(mPosX <= 6170) mPosX+=2;
            }

            SDL_RenderClear(renderer);
            render_map(renderer, mapp, camera);
            render_items(renderer, item, camera.x);

            for(int i=0; i<=9; i++) monster[i].render(camera.x, camera.y, renderer);
            boss.render(camera.x, camera.y, renderer, SpriteClips);

            this->render(camera.x, camera.y, renderer, SpriteClips);
            slash_frame = render_super_slash(renderer, superslash_left, superslash_right, slash_frame, slash_distance, direction, camera.x, monster, boss);
            rep = render_meteo(mPosX, rep, meteo_frame, danger_sign, meteo, renderer, camera.x, health.w);
            SDL_RenderPresent(renderer);

            fight_scene++;
        }
    }

    //Down: Slide
    if(keystates[SDL_SCANCODE_DOWN])
    {
        currentClip = &SpriteClips[10];
        int i=15;
        while(i--)
        {
            if(mTexture == right) mPosX+=i;
            else mPosX-=i;

            camera.x = mPosX - camera.w/2;
            camera.y = mPosY - camera.h/2;
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

            if(boss.enter_boss_stage(mPosX))
            {
                if(mPosX <= 5410) mPosX = 6175;
                boss.move(mPosX, SpriteClips);
                camera.x = LEVEL_WIDTH - camera.w;
                camera.y = LEVEL_HEIGHT - camera.h;
                if(mPosX <= 6170) mPosX+=2;
            }

            SDL_RenderClear(renderer);
            render_map(renderer, mapp, camera);
            render_items(renderer, item, camera.x);

            for(int i=0; i<=9; i++) monster[i].render(camera.x, camera.y, renderer);
            boss.render(camera.x, camera.y, renderer, SpriteClips);

            this->render(camera.x, camera.y, renderer, SpriteClips);
            slash_frame = render_super_slash(renderer, superslash_left, superslash_right, slash_frame, slash_distance, direction, camera.x, monster, boss);

            rep = render_meteo(mPosX, rep, meteo_frame, danger_sign, meteo, renderer, camera.x, health.w);

            SDL_RenderPresent(renderer);
        }
    }

    //Special Attack
    if(keystates[SDL_SCANCODE_X])
    {
        if(mTexture == left) direction = false;
        else direction = true;

        slash_frame = mPosX + currentClip->w;
        slash_distance = mPosX + currentClip->w;

        int special_attack = 210;
        while(special_attack/15 <= 16)
        {
            currentClip = &SpriteClips[special_attack/15];
            for(int i=0; i<=9; i++) monster[i].move(mPosX, SpriteClips);
            for(int i=0; i<=9; i++) this->hits_monster_status(monster[i], SpriteClips);
            this->hits_boss_status(boss, SpriteClips);

            if(boss.enter_boss_stage(mPosX))
            {
                boss.move(mPosX, SpriteClips);
                camera.x = LEVEL_WIDTH - camera.w;
                camera.y = LEVEL_HEIGHT - camera.h;
                if(mPosX <= 6170) mPosX+=2;
            }

            SDL_RenderClear(renderer);
            render_map(renderer, mapp, camera);
            render_items(renderer, item, camera.x);

            for(int i=0; i<=9; i++) monster[i].render(camera.x, camera.y, renderer);
            boss.render(camera.x, camera.y, renderer, SpriteClips);

            this->render(camera.x, camera.y, renderer, SpriteClips);

            rep = render_meteo(mPosX, rep, meteo_frame, danger_sign, meteo, renderer, camera.x, health.w);

            SDL_RenderPresent(renderer);
            special_attack++;
        }
        power.w = 0;
    }
}

void Knight::stand_still(SDL_Event &e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_RIGHT: mVelX++; break;
            case SDLK_LEFT: mVelX--; break;
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
}

void Knight::hits_monster_status(Monster &monster, SDL_Rect SpriteClips[])
{
    if(mPosX < monster.mPosX && mTexture == right)
    {
        if(monster.mPosX - mPosX > 30 && monster.mPosX - mPosX < 180 && currentClip == &SpriteClips[8])
        {
            if(monster.path_right == "monster2.png" && monster.path_left == "monster1.png") monster.currentClip = &SpriteClips[6];
            if(monster.path_right == "monster2.png" && monster.path_left == "monster1.png") monster.mPosX+=3;

            if(monster.health.w > 0)
            {
                monster.health.w--;
                if(power.w < 50) power.w++;
            }
            else monster.currentClip = &SpriteClips[13];
        }
    }
    else if(mPosX >= monster.mPosX && mTexture == left)
    {
        if(mPosX - monster.mPosX > 0 && mPosX - monster.mPosX < 120 && currentClip == &SpriteClips[8])
        {
            if(monster.path_right == "monster2.png" && monster.path_left == "monster1.png") monster.currentClip = &SpriteClips[6];
            if(monster.path_right == "monster2.png" && monster.path_left == "monster1.png") monster.mPosX-=3;

            if(monster.health.w > 0)
            {
                monster.health.w--;
                if(power.w < 50) power.w++;
            }
            else monster.currentClip = &SpriteClips[13];
        }
    }
}

void Knight::being_hit_status(Monster &monster, SDL_Rect SpriteClips[])
{
    if(mPosX < monster.mPosX)
    {
        if(monster.mPosX - mPosX > 0 && monster.mPosX - mPosX < 130 && monster.fight_scene == 250)
        {
            if(health.w >= 0 && monster.currentClip != &SpriteClips[13]) health.w-=5;
        }
    }
    else
    {
        if(mPosX - monster.mPosX > 0 && mPosX - monster.mPosX < 90 && monster.fight_scene == 250)
        {
            if(health.w >= 0 && monster.currentClip != &SpriteClips[13]) health.w-=5;
        }
    }
}

void Knight::hits_boss_status(Boss &boss, SDL_Rect SpriteClips[])
{
    if(mPosX > boss.mPosX)
    {
        if(mPosX - boss.mPosX <= 150 && boss.stunt == true && currentClip == &SpriteClips[8])
        {
            if(boss.health.w != 0)
            {
                boss.health.w--;
                if(power.w < 50) power.w++;
            }
            else boss.currentClip = &SpriteClips[13];
        }
    }
    else if(mPosX <= boss.mPosX)
    {
        if(boss.mPosX - mPosX <= 180 && boss.stunt == true && currentClip == &SpriteClips[8])
        {
            if(boss.health.w != 0)
            {
                boss.health.w--;
                if(power.w < 50) power.w++;
            }
            else boss.currentClip = &SpriteClips[13];
        }
    }
}

void Knight::being_hit_by_boss_status(Boss &boss, SDL_Rect SpriteClips[])
{
    if(mPosX < boss.mPosX && boss.mTexture == boss.left)
    {
        if(boss.mPosX - mPosX <=80 && boss.mPosX - mPosX >= 60 && boss.launch == true && currentClip != &SpriteClips[10])
        {
            if(health.w >= 0) health.w-=2;
        }
    }
    else if(mPosX >= boss.mPosX && boss.mTexture == boss.right)
    {
        if(mPosX - boss.mPosX <= 100 && mPosX - boss.mPosX >= 70 && boss.launch == true && currentClip != &SpriteClips[10])
        {
            if(health.w >= 0) health.w-=2;
        }
    }

    //
    if(boss.currentClip == &SpriteClips[20] || boss.currentClip == &SpriteClips[21])
    {
        if(boss.mTexture == boss.left)
        {
            if(mPosX >= 6815 && mPosX <= 6960) health.w--;
        }
        else if(boss.mTexture == boss.right)
        {
            if(mPosX >=6350 && mPosX <= 6450) health.w--;
        }
    }


    if(boss.currentClip == &SpriteClips[22] || boss.currentClip == &SpriteClips[23])
    {
        if(boss.mTexture == boss.left)
        {
            if(mPosX >= 6735 && mPosX <= 6814) health.w--;
        }
        else if(boss.mTexture == boss.right)
        {
            if(mPosX >= 6451 && mPosX <= 6580) health.w--;
        }
    }

    if(boss.currentClip == &SpriteClips[24] || boss.currentClip == &SpriteClips[25])
    {
        if(boss.mTexture == boss.left)
        {
            if(mPosX >= 6535 && mPosX <= 6734) health.w--;
        }
        else if(boss.mTexture == boss.right)
        {
            if(mPosX >= 6581 && mPosX <= 6770) health.w--;
        }
    }
    if(boss.currentClip == &SpriteClips[26] || boss.currentClip == &SpriteClips[27])
    {
        if(boss.mTexture == boss.left)
        {
            if(mPosX >= 6260 && mPosX <= 6534) health.w--;
        }
        else if(boss.mTexture == boss.right)
        {
            if(mPosX >= 6771 && mPosX <= 7055) health.w--;
        }
    }
}

void Knight::render(int camX, int camY, SDL_Renderer* renderer, SDL_Rect SpriteClips[])
{

    //Health
    if(mTexture == right)
    {
        health.x = mPosX + currentClip->w/2 - 50 - camX;
        if(currentClip == &SpriteClips[8]) health.x -= 50;
    }
    else
    {
        health.x = mPosX + currentClip->w/2 - 20 - camX;
        if(currentClip == &SpriteClips[8]) health.x -= 50;
    }

    health.y = mPosY + 160;

    health_border.x = health.x - 2;
    health_border.y = health.y - 1;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, &health_border);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &health);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //Power bar
    power.x = health.x;
    power.y = health.y - 10;

    power_border.x = power.x - 2;
    power_border.y = power.y -1;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer, &power_border);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    SDL_RenderFillRect(renderer, &power);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect quadrad = {mPosX - camX, mPosY - camY, currentClip->w, currentClip->h};
    SDL_RenderCopy(renderer, mTexture, currentClip, &quadrad);
}//





