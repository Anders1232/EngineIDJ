#include "GameObject.h"
#include "Rect.h"

class EmptyGameObject : public GameObject
{
public:
	EmptyGameObject(){}
	~EmptyGameObject(){}


	void Update(float dt ){}
	void Render(){}
	bool IsDead(void){return false;}
	void RequestDelete(void){}

	void NotifyCollision(GameObject &other){}
	Rect GetWorldRenderedRect(void) const{
		Rect rect;
		return rect;
	}
	bool Is(string type){return  "EmptyGameObject" == type;}


};