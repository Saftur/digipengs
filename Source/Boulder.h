/**
 * @file Boulder.h
 * @author Connor Meyers
 * @date 2019/01/22
 * @brief Object Header for the Boulder obstacle
 */

#pragma once

#include "AEEngine.h"
#include "object.h"
#include "Map.h"

#define BOULDER_TINY_SIZE   LANE_WIDTH
#define BOULDER_NORMAL_SIZE LANE_WIDTH * 2
#define BOULDER_BIG_SIZE    LANE_WIDTH * 3
#define BOULDER_GIANT_SIZE  LANE_WIDTH * 4

#define BOULDER_TINY_TEXTURE   TEXTURES.test
#define BOULDER_NORMAL_TEXTURE TEXTURES.test
#define BOULDER_BIG_TEXTURE    TEXTURES.test
#define BOULDER_GIANT_TEXTURE  TEXTURES.test

typedef struct BoulderInfo * BoulderInfoPtr;

 /**
  * @struct _boulderTypes
  * @brief All of the different types of boulders that can be created
  */
struct _boulderTypes
{
    BoulderInfoPtr tiny,   ///< Covers one lane
                   normal, ///< Covers two lanes
                   big,    ///< Covers three lanes
                   giant;  ///< Covers four lanes
};

/**
 * @var extern _boulderTypes BOULDER_TYPES
 * @brief Global struct to access all of the different boulders
 */
extern struct _boulderTypes BOULDER_TYPES;

/**
 * @brief Initializes boulder data
 */
void Boulder_intialize();

/**
 * @brief Frees all allocated memory and calls any ending functions
 */
void Boulder_shutdown();

/**
 * @brief Create new boulder
 * @param type Type of boulder to create
 * @param pos Position to create boulder at
 * @return New boulder
 */
Object *Boulder_new(BoulderInfoPtr type, AEVec2 pos);
