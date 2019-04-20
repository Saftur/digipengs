/**
 * Project: DigitalPenguins
 * All content © 2019 DigiPen (USA) Corporation, all rights reserved.
 * @file PlayerParticles.h
 * @author Arthur Bouvier
 * @brief Player particle functions
 */
#pragma once

#include "Player.h"

typedef struct PlayerParticleData {
    PlayerData *playerData;
    int modeSwitch;
} PlayerParticleData;

Particle *particleSpawnFunc(PlayerParticleData *data);
float particleSpawnTimeFunc(PlayerParticleData *data);
