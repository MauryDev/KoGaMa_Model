#pragma once
#include "i16Vector.h"
#include "byte.h"
#include <array>
using MaterialsInfo = std::array<byte, 6>;
using CornersInfo = std::array<byte, 8>;

struct CubeInfo
{
	MaterialsInfo materials;
	CornersInfo corners;
	static CornersInfo IdentityByteCorners;
	CubeInfo();
	CubeInfo(byte material);
	CubeInfo(MaterialsInfo materials);
	CubeInfo(MaterialsInfo materials, CornersInfo cornersinfo);

	static MaterialsInfo CreateMaterials(byte basematerial);
	bool IsBaseMaterials();
	bool IsIdentityByteCorners();

};