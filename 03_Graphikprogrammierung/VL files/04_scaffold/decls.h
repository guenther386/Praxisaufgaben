#pragma once // ensure that header is only read once
// enumerate type definitions
enum Number { ZERO,MINUS_ONE=-1,ANOTHER_ZERO,ONE,FIVE=5,SIX };
// declare a compound type
struct Vec3d
{
	double x,y,z;
}; // don't forget semicolon at the end!!!

// global variable - to be declared again in exactly one source
extern int max_integer;
// common function - to be declared again in exactly one source
extern int faculty(int n);
