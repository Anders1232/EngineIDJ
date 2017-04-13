#include "Vec2.h"
#include "Error.h"
#include <cmath>

Vec2::Vec2(void): x(0.0), y(0.0)
{
}
Vec2::Vec2(float x, float y): x(x), y(y)
{
}
Vec2::Vec2(Vec2 const &b): x(b.x), y(b.y)
{
}
Vec2 Vec2::operator+(Vec2 const &b)const
{
	return Vec2(x+b.x, y+b.y);
}
Vec2 Vec2::operator-(Vec2 const &b) const
{
	return Vec2(x-b.x, y-b.y);
}
Vec2 Vec2::operator*(float b) const
{
	return Vec2(this->Magnitude()*b, 0).Rotate(Inclination());//coordenadas polares OP
	return Vec2(x*b, y*b);//esse aqui zoa a magnetude
}

Vec2& Vec2::operator=(Vec2 const &b)
{
	x= b.x;
	y= b.y;
	return *this;
}

float Vec2::Magnitude(void)const
{
	return sqrt(x*x+ y*y);
}
void Vec2::Normalize(void)
{
	float norm= Magnitude();
	x=x/norm;
	y=y/norm;
//	return Vec2(x/norm, y/norm);
}
float Vec2::DistanceTo(Vec2 const &b) const
{
	return ((*this)-b).Magnitude();
}
float Vec2::Inclination(void) const
{
	return atan2(y, x);
}
float Vec2::Inclination(Vec2 const &b) const
{
	return ((*this)-b).Inclination();
}

bool Vec2::IsInRect(SDL_Rect const &rect) const
{
	int xMax, yMax;
	xMax= rect.x+rect.w;
	yMax= rect.y+rect.h;//o eixo y crece para baixo, ver se tem que somar ou subtrair
	return (rect.x<=x && x < xMax && rect.y <= y && y < yMax);//caso o ponto mais próximo da origem seja (0,0)
//	return (rect.x<x && x <= xMax && rect.y < y && y <= yMax);//caso o ponto mais próximo da origem seja (1,1)
}

Vec2 Vec2::Rotate(float angle) const
{
	return Vec2(x*cos(angle)-y*sin(angle), y*cos(angle)+x*sin(angle));
}
Vec2& Vec2::operator+=(Vec2 const &b)
{
	*this= *this+b;
	return *this;
}
Vec2& Vec2::operator-=(Vec2 const &b)
{
	*this= *this-b;
	return *this;
}
Vec2 Vec2::FromPolarCoord(float magnetude, float angle)
{
	return Vec2(magnetude, 0).Rotate(angle);
}
Vec2 Vec2::MemberMult(float const &b)const
{
	return Vec2(x*b, y*b);
}


