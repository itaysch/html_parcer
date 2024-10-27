#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* array;
    int capacity;
    int current_size;
}Vector;
Vector* createVector(const int size);
void append(Vector* vector, const char value);
void resize(Vector* vector);
void set(const Vector* vector, const int index, const char value);
char get(const Vector* vector, const int index);
void removeAt(Vector* vector, const int index);
void insertAt(Vector* vector, const int index, const char value);
void printVector(const Vector* vector);
void freeVector(Vector* vector);

#endif //VECTOR_H