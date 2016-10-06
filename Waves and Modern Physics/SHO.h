#pragma once
#include <cmath>

class SHO
{
public:

	float k = 1; // spring constant [N*s^-1]
	float m = 1; // mass [kg]

	float A = 1; // amplitude
	float w = 1; // omega, angular frequency [radians]
	float t = 0; // time [seconds]
	float phi = 0; // phase angle [radians]

	float x(float t); // displacement
	float v(float t); // velocity
	float a(float t); // acceleration
};