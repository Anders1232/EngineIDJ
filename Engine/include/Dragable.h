/*usar friends pra pegar local()*/
#include "Component.h"

class Dragable: public Component
{
public:
	Dragable();
	~Dragable();
	void Is(int);
	void Update();
private:
	bool IsDraging;
};