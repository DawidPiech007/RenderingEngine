#pragma once
#include <string>
#include <math.h>

static float sameColor = 0.001f;


class LightIntensity
{
public:
	float r, g, b;

	LightIntensity(float R, float G, float B);
	LightIntensity(float R, float G);
	LightIntensity(float R);
	LightIntensity();

	void operator()(float R, float G, float B);
	void operator()(float R, float G);
	void operator()(float R);

	void add(float R, float G, float B);

	LightIntensity operator+(const LightIntensity& light);
	LightIntensity operator-(const LightIntensity& light);
	LightIntensity operator*(const LightIntensity& light);
	LightIntensity operator*(float num);
	LightIntensity operator/(float num);
	bool operator==(const LightIntensity& light);
	LightIntensity& operator+=(const LightIntensity& light);
	LightIntensity& operator-=(const LightIntensity& light);
	LightIntensity& operator*=(const float& num);
	LightIntensity& operator/=(const float& num);
	std::string ToString();

};

