#include "LightIntensity.h"

LightIntensity::LightIntensity(float R, float G, float B) : r(R), g(G), b(B) {}

LightIntensity::LightIntensity(float R, float G) : r(R), g(G), b(0) {}

LightIntensity::LightIntensity(float R) : r(R), g(0), b(0) {}

LightIntensity::LightIntensity() : r(0), g(0), b(0) {}

void LightIntensity::operator()(float R, float G, float B)
{
	r = R;
	g = G;
	b = B;
}

void LightIntensity::operator()(float R, float G)
{
	r = R;
	g = G;
}

void LightIntensity::operator()(float R)
{
	r = R;
}

LightIntensity LightIntensity::operator+(const LightIntensity& light)
{
	return LightIntensity(this->r + light.r, this->g + light.g, this->b + light.b);
}

LightIntensity LightIntensity::operator-(const LightIntensity& light)
{
	return LightIntensity(this->r - light.r, this->g - light.g, this->b - light.b);
}

LightIntensity LightIntensity::operator*(const LightIntensity& light)
{
	return LightIntensity(this->r * light.r, this->g * light.g, this->b * light.b);
}

LightIntensity LightIntensity::operator*(float num)
{
	return LightIntensity(this->r * num, this->g * num, this->b * num);
}

LightIntensity LightIntensity::operator/(float num)
{
	return LightIntensity(this->r / num, this->g / num, this->b / num);
}

bool LightIntensity::operator==(const LightIntensity& light)
{
	if (fabs(r - light.r) > sameColor)
		return false;
	if (fabs(g - light.g) > sameColor)
		return false;
	if (fabs(b - light.b) > sameColor)
		return false;
	return true;
}

LightIntensity& LightIntensity::operator+=(const LightIntensity& light)
{
	this->r += light.r;
	this->g += light.g;
	this->b += light.b;
	return *this;
}

LightIntensity& LightIntensity::operator-=(const LightIntensity& light)
{
	this->r -= light.r;
	this->g -= light.g;
	this->b -= light.b;
	return *this;
}

LightIntensity& LightIntensity::operator*=(const float& num)
{
	this->r *= num;
	this->g *= num;
	this->b *= num;
	return *this;
}

LightIntensity& LightIntensity::operator/=(const float& num)
{
	this->r *= num;
	this->g *= num;
	this->b *= num;
	return *this;
}

std::string LightIntensity::ToString()
{
	std::string text = "  r = " + std::to_string(r) + "\n";
	text += "  g = " + std::to_string(g) + "\n";
	text += "  b = " + std::to_string(b) + "\n";
	return text;
}
