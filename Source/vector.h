/**
 * @file Vector.h
 * @author Arthur Bouvier
 * @brief C++-style NULL-type vector class
 */
#pragma once

typedef struct vector vector; ///< @brief vector forward declaration

typedef void *(*vector_copyfunc)(void *item); ///< Function type to copy item
typedef void(*vector_delfunc)(void *item);    ///< Function type to delete item

/**
 * @brief Create new vector
 * @param max      Starting array allocation size
 * @param copyfunc Item copy function
 * @param delfunc  Item delete function
 * @return New vector
 */
vector *vector_new(size_t max, vector_copyfunc copyfunc, vector_delfunc delfunc);
/** 
 * @brief Delete vector
 * @param vec vector to delete
 */
void vector_delete(vector *vec);

/**
 * @brief Get size of vector
 * @param vec vector to get size of
 * @return Size of vector
 */
size_t vector_size(vector *vec);
/**
 * @brief Get max size of vector
 * @param vec vector to get max size of
 * @return Max size of vector
 */
size_t vector_max_size(vector *vec);
/**
 * @brief Check if vector is empty
 * @param vec vector to check
 * @return Whether it is empty
 */
int vector_empty(vector *vec);
/**
 * @brief Reserve space for the vector array
 * @param vec vector to reserve for
 * @param max New max size of vector
 */
void vector_reserve(vector *vec, size_t max);

/**
 * @brief Get item in vector
 * @param vec vector to get from
 * @param i   Index at which to get item
 * @return Item in vector at given index
 */
void *vector_at(vector *vec, unsigned i);

/**
 * @brief Add item to the back of a vector
 * @param vec  vector to add to
 * @param item Item to add
 */
void vector_push_back(vector *vec, void *item);

/**
 * @brief Erase item from vector
 * @param vec vector to erase fom
 * @param i   Index of item to delete
 */
void vector_erase(vector *vec, unsigned i);

/**
 * @brief Delete all items in vector
 * @param vec vector to clear
 */
void vector_clear(vector *vec);

