#pragma once
#include <string>

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

	LightIntensity operator+(LightIntensity& light);
	LightIntensity operator-(LightIntensity& light);
	LightIntensity operator*(float num);
	LightIntensity operator/(float num);
	LightIntensity& operator+=(LightIntensity& light);
	LightIntensity& operator-=(LightIntensity& light);
	LightIntensity& operator*=(float& num);
	LightIntensity& operator/=(float& num);
	std::string ToString();

};

