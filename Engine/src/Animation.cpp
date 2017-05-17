#include "Animation.h"
#include "Camera.h"

Animation::Animation
(
	float x,
	float y,
	float rotation,
	string sprite,
	int frameCount,
	float frameTime,
	bool ends
): GameObject(), endTimer(), timeLimit(frameCount*frameTime), onetimeOnly(ends), sp(sprite, frameTime, frameCount)
{
	box= Vec2(x, y);
	this->rotation= rotation;
}
void Animation::Update(float dt)
{
	sp.Update(dt);
	endTimer.Update(dt);
}
void Animation::Render(void)
{
	sp.Render(box.x-Camera::pos.x, box.y-Camera::pos.y, rotation, true);
}
Rect Animation::GetWorldRenderedRect(void) const
{
	Rect rect;
	rect.x= box.x-Camera::pos.x;
	rect.y= box.y-Camera::pos.y;
	rect.w= sp.GetWidth();
	rect.h= sp.GetHeight();
	
	rect= rect * Camera::GetZoom();
	
	return rect+Camera::pos;
}
bool Animation::IsDead(void)
{
	if(onetimeOnly)
	{
		if(endTimer.Get()> timeLimit)
		{
			return true;
		}
	}
	return false;
}
void Animation::NotifyCollision(GameObject &other)
{}
bool Animation::Is(string type)
{
	return type=="Animation";
}

