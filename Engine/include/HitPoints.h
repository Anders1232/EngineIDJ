#include "Component.h"
#include "Sprite.h"

class HitPoints : public Component
{
	public:
		HitPoints(float hp);
		~HitPoints();
		
		void Update(GameObject &associated);
		bool Is(ComponentType) const;

	private:
		float hp;
		Sprite healthBar;
		Sprite healthColor;
};