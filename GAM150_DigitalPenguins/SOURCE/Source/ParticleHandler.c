/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file ParticleHandler.c
 * @author Arthur Bouvier
 * @brief Particle system implementation
 */
#include "stdafx.h"

#include "ParticleHandler.h"
#include "ImageHandler.h"
#include "MeshHandler.h"
#include "Utils.h"

static int Particle_update(Particle *p, float dt);
static void Particle_draw(Particle *p);

ParticleEmitter *ParticleEmitter_new(AEVec2 pos, float rot, int enable, unsigned maxParticles,
                                     ParticleSpawnFunc spawnFunc, ParticleSpawnSpeedFunc spawnSpeedFunc,
                                     void *spawnFuncsData) {
    ParticleEmitter *pe = malloc(sizeof(ParticleEmitter));
    pe->pos = pos;
    pe->rot = rot;
    pe->enable = enable;
    pe->maxParticles = maxParticles;
    pe->spawnFunc = spawnFunc;
    pe->spawnSpeedFunc = spawnSpeedFunc;
    pe->spawnFuncsData = spawnFuncsData;
    pe->particles = vector_new(maxParticles, NULL, free);
    pe->timer = 0.f;
    return pe;
}

void ParticleEmitter_delete(ParticleEmitter *pe) {
    vector_delete(pe->particles);
    free(pe);
}

void ParticleEmitter_update(ParticleEmitter *pe, float dt) {
    for (unsigned i = 0; i < vector_size(pe->particles); i++) {
        Particle *p = vector_at(pe->particles, i);
        if (!Particle_update(p, dt)) {
            vector_erase(pe->particles, i);
            i--;
        }
    }

    if (pe->enable && pe->spawnSpeedFunc(pe->spawnFuncsData) > 0.f) {
        if (pe->timer >= 1.f / pe->spawnSpeedFunc(pe->spawnFuncsData)) {
            if (vector_size(pe->particles) < pe->maxParticles) {
                Particle *p = pe->spawnFunc(pe->spawnFuncsData);
                AEVec2Rotate(&p->pos, &p->pos, pe->rot);
                AEVec2Rotate(&p->vel, &p->vel, pe->rot);
                p->rot += pe->rot;

                AEVec2Add(&p->pos, &pe->pos, &p->pos);
                vector_push_back(pe->particles, p);
                pe->timer = 0.f;//pe->spawnSpeedFunc(pe->spawnFuncsData);
            }
        } else pe->timer += dt;
    } else pe->timer = 0.f;
}

void ParticleEmitter_draw(ParticleEmitter *pe) {
    for (unsigned i = 0; i < vector_size(pe->particles); i++)
        Particle_draw(vector_at(pe->particles, i));
}

Particle *Particle_new() {
    Particle *p = calloc(1, sizeof(Particle));
    p->alpha = 1.f;
    return p;
}

static int Particle_update(Particle *p, float dt) {
    if (p->life <= 0.f)
        return 0;
    p->life -= dt;

    if (p->vel.x != 0.f || p->vel.y != 0.f) {
        if (p->deccel != 0.f) {
            AEVec2 deccel;
            AEVec2Normalize(&deccel, &p->vel);
            AEVec2Scale(&deccel, &deccel, p->deccel * dt);
            AEVec2Sub(&p->vel, &p->vel, &deccel);
            if ((deccel.x < 0.f && p->vel.x < 0.f) || (deccel.x > 0.f && p->vel.x > 0.f)) {
                p->vel.x = 0.f;
                p->vel.y = 0.f;
            }
        }
        AEVec2 move;
        AEVec2Scale(&move, &p->vel, dt);
        AEVec2Add(&p->pos, &p->pos, &move);
    }

    if (p->rotVel != 0.f) {
        if (p->rotDeccel != 0.f) {
            p->rotVel -= p->rotDeccel * dt;
            if ((p->rotDeccel < 0.f && p->rotVel < 0.f) || (p->rotDeccel > 0.f && p->rotVel > 0.f))
                p->rotVel = 0.f;
        }
        p->rot += p->rotVel * dt;
    }

    if (p->sclChange.x != 0.f || p->sclChange.y != 0.f) {
        AEVec2 sclChange;
        AEVec2Scale(&sclChange, &p->sclChange, dt);
        AEVec2Add(&p->scl, &p->scl, &sclChange);
        if (p->scl.x <= 0.f || p->scl.y <= 0.f)
            return 0;
    }

    if (p->alphaChange != 0.f) {
        p->alpha += p->alphaChange;
        if (p->alpha <= 0.f)
            return 0;
    }

    return 1;
}

static void Particle_draw(Particle *p) {
    ImageHandler_fullDrawTexture(MeshHandler_getSquareMesh(), p->texture, p->pos, p->scl.x, p->scl.y, p->rot, p->alpha);
}
