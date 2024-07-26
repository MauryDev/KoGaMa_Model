#include "i16Vector.h"


bool i16Vector::operator==(const i16Vector& otherv) const
{
	return this->x == otherv.x &&
		this->y == otherv.y &&
		this->z == otherv.z;
}
