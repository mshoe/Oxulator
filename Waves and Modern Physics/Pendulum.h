#pragma once
#include <cmath>
#include <iostream>

class Pendulum
{
public:

	float L = 1; // Length
	float m = 1; // Point Mass
	float g = -9.81; // Gravitational acceleration
	float t = 0; // Time
	float theta = 0; // Angle
	float d_theta = 0;

	float x = 1; // X coordinate of mass
	float y = 1; // Y coordinate of mass

	float vx = 0; // X velocity m/s
	float vy = 0; // Y velocity m/s

	void updateXY();
	void updatePendulum(float deltaTime);

};