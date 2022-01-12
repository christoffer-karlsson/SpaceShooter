#include "entity_object.h"
#include "..\debug\debug_display.h"
#include "..\buffer\offscreen_buffer.h"
#include "collision_event.h"
#include <vector>

class collision_detect
{
	private:
	static std::vector<std::shared_ptr<entity_object>> EntityCollisionPositions;
	
	public:
	void Push(std::shared_ptr<entity_object> Entity);
	void RectangleCheck();

	public:
	collision_detect();
};