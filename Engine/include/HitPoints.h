#include "Component.h"
#include "Sprite.h"

class HitPoints : public Component
{
	public:
		HitPoints(float hp);
		~HitPoints();
		
		void Update(GameObject &associated, float dt);
		bool Is(ComponentType) const;

	private:
		float hp;
		Sprite healthBar;
		Sprite healthColor;
};
