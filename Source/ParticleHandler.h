/**
 * @file ParticleHandler.h
 * @author Arthur Bouvier
 * @brief Particle system
 */
#pragma once

#include <AEEngine.h>
#include "vector.h"

typedef struct Particle {
    AEVec2 pos;
    AEVec2 vel;
    float deccel;

    float rot;
    float rotVel;
    float rotDeccel;

    AEVec2 scl;
    AEVec2 sclChange;
    float alpha;
    float alphaChange;

    float life;

    AEGfxTexture *texture;
} Particle;

/** @brief Generates particle spawn data */
typedef Particle*(*ParticleSpawnFunc)();
/** @brief Gives particle spawn time offset */
typedef float(*ParticleSpawnTimeFunc)();

typedef struct ParticleEmitter {
    AEVec2 pos;
    float rot;
    int enable;
    unsigned maxParticles;

    ParticleSpawnFunc spawnFunc;
    ParticleSpawnTimeFunc spawnTimeFunc;

    vector *particles;
    float timer;
} ParticleEmitter;

ParticleEmitter *ParticleEmitter_new(AEVec2 pos, float rot, int enable, unsigned maxParticles,
                                     ParticleSpawnFunc spawnFunc, ParticleSpawnTimeFunc spawnTimeFunc);
void ParticleEmitter_delete(ParticleEmitter *pe);

void ParticleEmitter_update(ParticleEmitter *pe, float dt);
void ParticleEmitter_draw(ParticleEmitter *pe);

Particle *Particle_new();
