#include "aura.h"

int spritesheet_Init(const char* image, aura_Spritesheet* spritesheet)
{
    int ret = sprite_Init(image, &spritesheet->sprite);
    return ret;
}

void spritesheet_Tick(double now, aura_Spritesheet* spritesheet)
{
    if (timer_Tick(now, &spritesheet->timer))
    {
        spritesheet->frame += 1;
        if (spritesheet->frame > spritesheet->cols) spritesheet->frame = 0;
    }
}
