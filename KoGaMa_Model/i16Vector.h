#pragma once
#include <cinttypes>
#include <type_traits>
struct i16Vector
{
	struct KeyHasher
	{
		size_t operator()(const i16Vector& k) const
		{
			using std::hash;

			return ((hash<int16_t>()(k.x)
				^ (hash<int16_t>()(k.y) << 1)))
				^ (hash<int16_t>()(k.z) << 1);
		}
	};

	int16_t x;
	int16_t y;
	int16_t z;
	
	bool operator==(const i16Vector& otherv) const;
};