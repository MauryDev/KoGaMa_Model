#include "CubeInfo.h"

CornersInfo CubeInfo::IdentityByteCorners = {
	20,120,124,24,4,104,100,0
};

CubeInfo::CubeInfo()
{
	materials = {};
	corners = {};
	
}

CubeInfo::CubeInfo(byte material)
{
	materials = CreateMaterials(material);
	corners = IdentityByteCorners;
}

CubeInfo::CubeInfo(MaterialsInfo materials)
{
	this->materials = materials;
	this->corners = IdentityByteCorners;
}

CubeInfo::CubeInfo(MaterialsInfo materials, CornersInfo cornersinfo)
{
	this->materials = materials;
	this->corners = cornersinfo;
}

MaterialsInfo CubeInfo::CreateMaterials(byte basematerial)
{
	std::array<byte, 6> ret{};
	for (size_t i = 0; i < 6; i++)
	{
		ret[i] = basematerial;
	}
	return ret;
}

bool CubeInfo::IsBaseMaterials()
{
	auto material = materials[0];
	for (size_t i = 1; i < 6; i++)
	{
		if (material != materials[i])
		{
			return false;
		}
	}
	return true;
}

bool CubeInfo::IsIdentityByteCorners()
{
	for (size_t i = 0; i < 8; i++)
	{
		if (corners[i] != IdentityByteCorners[i])
		{
			return false;
		}
	}
	return true;
}
