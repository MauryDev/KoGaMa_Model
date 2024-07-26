#pragma once
#include "byte.h"
enum class CubeFlags: byte
{
	None = 0b0,
	BaseMaterial = 0b1,
	IdentityByteCorners = 0b10,
	PosX_8b = 0b100,
	PosY_8b = 0b1000,
	PosZ_8b = 0b10000,
	PosIdentity = 0b100000
};
CubeFlags operator|(CubeFlags flag1, CubeFlags flag2);
CubeFlags operator&(CubeFlags flag1, CubeFlags flag2);
CubeFlags operator~(CubeFlags flag1);
CubeFlags operator^(CubeFlags flag1, CubeFlags flag2);

CubeFlags& operator|= (CubeFlags& a, CubeFlags b);
CubeFlags& operator&= (CubeFlags& a, CubeFlags b);
inline CubeFlags& operator^= (CubeFlags& a, CubeFlags b);