#include "CubeFlags.h"

CubeFlags operator|(CubeFlags flag1, CubeFlags flag2)
{
    return static_cast<CubeFlags>((byte)flag1 | (byte)flag2);
}


CubeFlags operator&(CubeFlags flag1, CubeFlags flag2)
{
    return static_cast<CubeFlags>((byte)flag1 & (byte)flag2);
}

CubeFlags operator~(CubeFlags flag1)
{
    return static_cast<CubeFlags>(~(byte)flag1);
}

CubeFlags operator^(CubeFlags flag1, CubeFlags flag2)
{
    return static_cast<CubeFlags>((byte)flag1 ^ (byte)flag2);
}

CubeFlags& operator|=(CubeFlags& flag1, CubeFlags flag2)
{
    return (CubeFlags&)((byte&)flag1 |= (byte)flag2);
}

CubeFlags& operator&=(CubeFlags& flag1, CubeFlags flag2)
{
    return (CubeFlags&)((byte&)flag1 &= (byte)flag2);
}

inline CubeFlags& operator^=(CubeFlags& flag1, CubeFlags flag2)
{
    return (CubeFlags&)((byte&)flag1 ^= (byte)flag2);
}
