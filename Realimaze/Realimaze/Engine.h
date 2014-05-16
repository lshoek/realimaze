#ifndef ENGINE
#define ENGINE

#include "Shape.h"
#include "Circle.h"
#include "WallList.h"

Circle * circle;
WallList list;

extern void CreateEngine(void);
extern void DestructEngine(void);
extern void Step(void);
#endif
