#pragma once
#include <cmath>

class SHO
{
public:
	SHO();
	
	void setKM(float k, float m) { this->k = k; this->m = m;}
	void setAwtphi(float A, float w, float t, float phi) {
		this->A = A; this->w = w; this->t = t; this->phi = phi;
	}

	float k; // spring constant [N*s^-1]
	float m; // mass [kg]

	float A; // amplitude
	float w; // omega, angular frequency [radians]
	float t; // time [seconds]
	float phi; // phase angle [radians]

	float x(float t); // displacement
	float v(float t); // velocity
	float a(float t); // acceleration
};