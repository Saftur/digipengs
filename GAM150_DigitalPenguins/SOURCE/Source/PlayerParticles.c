/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file PlayerParticles.c
 * @author Arthur Bouvier
 * @brief Player particle functions
 */
#include "stdafx.h"

#include "PlayerParticles.h"
#include "Utils.h"

Particle *particleSpawnFunc(PlayerParticleData *data) {
#define ROT_START       0.5f
#define ROT_START_LEFT  ROT_START
#define ROT_START_RIGHT (ROT_START + 1.f)
#define ROT_RANGE_UP    0.1f
#define ROT_RANGE_DOWN  0.1f
#define LIFE            0.25f
#define SCALE           15.f

    UNREFERENCED_PARAMETER(data);
    Particle *p = Particle_new();

    p->pos.x = data->modeSwitch / 2 < 1 ? -PLAYER_SCALE.x * 0.4f : PLAYER_SCALE.x * 0.125f;
    p->pos.y = 0.f;
    p->pos.y = (data->modeSwitch % 2 == 0 ? 1.f : -1.f) * PLAYER_SCALE.y * 0.125f;

    float rot = data->modeSwitch % 2 == 0 ? randrangef((ROT_START_LEFT - ROT_RANGE_UP) * PI, (ROT_START_LEFT + ROT_RANGE_DOWN) * PI) : 
                                            randrangef((ROT_START_RIGHT - ROT_RANGE_DOWN) * PI, (ROT_START_RIGHT + ROT_RANGE_UP) * PI);
    AEVec2FromAngle(&p->vel, rot);

    AEVec2 posAdd;
    AEVec2Scale(&posAdd, &p->vel, PLAYER_SCALE.y / 4.f);
    AEVec2Add(&p->pos, &p->pos, &posAdd);

    AEVec2Scale(&p->vel, &p->vel, randrangef(100, 150));

    AEVec2 velAdd;
    velAdd.x = data->playerData->speed * 0.75f;
    velAdd.y = 0.f;
    AEVec2Add(&p->vel, &p->vel, &velAdd);

    p->rotVel = 2.f * PI;

    p->life = LIFE;

    p->scl.x = SCALE;
    p->scl.y = SCALE;
    p->sclChange.x = -p->scl.x / p->life;
    p->sclChange.y = -p->scl.y / p->life;

    p->texture = TEXTURES.particle;

    data->modeSwitch = (data->modeSwitch + 1) % 4;

    return p;
#undef ROT_START
#undef ROT_START_LEFT
#undef ROT_START_RIGHT
#undef ROT_RANGE_UP
#undef ROT_RANGE_DOWN
#undef LIFE
#undef SCALE
}

float particleSpawnTimeFunc(PlayerParticleData *data) {
    return data->playerData->speed / data->playerData->speedcap * 80.f;
}
