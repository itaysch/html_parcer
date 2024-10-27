#include "vector.h"

Vector* createVector(const int size) {
    Vector* vector = (Vector*)malloc(sizeof(Vector));
    vector->array = (char*)malloc(size * sizeof(char));
    vector->capacity = size;
    vector->current_size = 0;
    return vector;
}

void append(Vector* vector, const char value) {
    if(vector->current_size == vector->capacity) {
        vector->capacity *= 2;
        vector->array = (char*)realloc(vector->array, vector->capacity * sizeof(char));
    }
    vector->array[vector->current_size++] = value;
}

void resize(Vector* vector) {
    vector->capacity *= 2;
    vector->array = (char*)realloc(vector->array, vector->current_size * sizeof(char));
}

void set(const Vector* vector, const int index, const char value) {
    if(index >= vector->current_size || index < 0) {
        printf("out of bounds\n");
        return;
    }
    vector->array[index] = value;
}

char get(const Vector* vector, const int index) {
    if(index >= vector->current_size || index < 0) {
        printf("out of bounds\n");
        return -1;
    }
    return vector->array[index];
}

void removeAt(Vector* vector, const int index) {
    if(index < 0 || index >= vector->current_size) {
        printf("out of bounds\n");
        return;
    }
    for(int i = index; i < vector->current_size - 1; i++) {
        vector->array[i] = vector->array[i + 1];
    }
    vector->current_size--;
}

void insertAt(Vector* vector, const int index, const char value) {
    if(index < 0 || index >= vector->current_size) {
        printf("out of bounds\n");
        return;
    }
    for(int i = vector->current_size - 1; i > index; i--) {
        vector->array[i] = vector->array[i - 1];
    }
    vector->array[index] = value;
    vector->current_size++;

}

void printVector(const Vector* vector) {
    for(int i = 0; i < vector->current_size; i++) {
        printf("%c ", vector->array[i]);
    }
}

void freeVector(Vector* vector) {
    free(vector->array);
    vector->current_size = 0;
    vector->capacity = 0;
}