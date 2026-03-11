#ifndef IO_H
#define IO_H

#include "AVL.h"
#include "heap.h"

void SAVE(AVL *T, Heap *h);
int LOAD(AVL *T, Heap *h,int *Prio);

#endif