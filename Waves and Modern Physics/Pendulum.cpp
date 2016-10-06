#include "Pendulum.h"

void Pendulum::updateXY()
{
	y = L - cos(theta);
	x = sin(theta) * L;
}

void Pendulum::updatePendulum(float deltaTime)
{
	float d2_theta = g/L * sin(theta);
	d_theta += d2_theta * deltaTime;
	theta += d_theta * deltaTime;
	
	//float d2_x = cos(theta) * sin(theta) * g;
	//float d2_y = sin(theta) * sin(theta) * g;

	//vx += d2_x * deltaTime; // Units makes sense m/s = m/s^2 * s
	//vy += d2_y * deltaTime;

	//x += vx * deltaTime; // Units make sense m = m/s * s
	//y += vy * deltaTime;

	//std::cout << y << std::endl;

	updateXY();
}
