/**
 * @file Vector.c
 * @author Arthur Bouvier
 * @brief vector implementation
 */
#include "stdafx.h"

#include "Vector.h"

struct vector {
	void **data;
	size_t size;
	size_t max;

	vector_copyfunc copyfunc;
	vector_delfunc delfunc;
};

vector *vector_new(size_t max, vector_copyfunc copyfunc, vector_delfunc delfunc) {
	vector *vec = malloc(sizeof(vector));
	vec->max = max;
	vec->size = 0;
	vec->data = malloc(sizeof(void*) * max);
	vec->copyfunc = copyfunc;
	vec->delfunc = delfunc;
	return vec;
}

void vector_delete(vector *vec) {
	vector_clear(vec);
	free(vec->data);
	free(vec);
}

size_t vector_size(vector *vec) {
	return vec->size;
}

size_t vector_max_size(vector *vec) {
	return vec->max;
}

int vector_empty(vector *vec) {
	return vec->size == 0;
}

void vector_reserve(vector *vec, size_t max) {
	if (max > vec->max) {
		vec->max = max;
		void *data = vec->data;
		vec->data = malloc(sizeof(void*) * max);
		memcpy(vec->data, data, sizeof(void*) * vec->size);
		free(data);
	}
}

void *vector_at(vector *vec, unsigned i) {
	return vec->data[i];
}

void vector_push_back(vector *vec, void *item) {
	if (vec->size + 1 >= vec->max)
		vector_reserve(vec, vec->max * 2);
	vec->data[vec->size++] = item;
}

void vector_erase(vector *vec, unsigned i) {
	if (i >= vec->size)
		return;
	vec->delfunc(vec->data[i]);
	memmove(vec->data + i, vec->data + i + 1, (vec->size - i - 1) * sizeof(void*));
	vec->size--;
}

void vector_clear(vector *vec) {
	for (unsigned i = 0; i < vec->size; i++)
		vec->delfunc(vec->data[i]);
	vec->size = 0;
}
