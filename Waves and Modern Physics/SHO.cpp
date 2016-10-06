#include "SHO.h"

float SHO::x(float t)
{
	return A*std::cos(w*t + phi);
}

float SHO::v(float t)
{
	return -w*A*std::sin(w*t + phi);
}

float SHO::a(float t)
{
	return -std::pow(w, 2)*A*std::cos(w*t + phi);
}
