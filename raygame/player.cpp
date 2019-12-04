#include "player.h"

bool customCollision(Vector2 v, Rectangle r) {
	if(v.x > r.x&&v.y>r.y&&v.y<r.y+r.height &&v.x<r.x+r.width) {
		return true;
	}
	return false;
}