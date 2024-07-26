#include "Model.h"
#include "CubeFlags.h"
#include "UtilsInt.h"
bool Model::AddCube(i16Vector pos, CubeInfo cube)
{
	auto findpos = this->cubesinfo.find(pos);
	if (findpos == cubesinfo.end())
	{
		cubesinfo.insert(std::make_pair(pos,cube));
		return true;

	}
	return false;

}

bool Model::ReplaceCube(i16Vector pos, CubeInfo cube)
{
	auto findpos = this->cubesinfo.find(pos);
	if (findpos != cubesinfo.end())
	{
		findpos->second = cube;
		return true;
	}
	return false;

}

std::tuple<CubeInfo, bool> Model::GetCube(i16Vector pos)
{
	auto findpos = this->cubesinfo.find(pos);
	if (findpos != cubesinfo.end())
	{
		return std::make_tuple(findpos->second,true);
	}
	return std::make_tuple(CubeInfo{}, false);
}

bool Model::RemoveCube(i16Vector pos)
{
	auto findpos = this->cubesinfo.find(pos);
	if (findpos != cubesinfo.end())
	{
		cubesinfo.erase(findpos);
		return true;
	}
	return false;
}

std::vector<byte> Model::ToBytes()
{
	std::vector<byte> ret{};
	for (auto& key_val : cubesinfo)
	{
		auto& pos = key_val.first;
		auto& cubeinfo = key_val.second;
		CubeFlags cubeflags = Model::GetFlags(pos,cubeinfo);


		InsertBytes(ret, cubeflags);
		if ((cubeflags & CubeFlags::PosIdentity) != CubeFlags::None)
		{
			if ((cubeflags & CubeFlags::PosX_8b) != CubeFlags::None)
			{
				int8_t posidentity = pos.x;
				InsertBytes(ret, posidentity);
			}
			else
			{
				InsertBytes(ret, pos.x);
			}
		}
		else
		{
			if ((cubeflags & CubeFlags::PosX_8b) != CubeFlags::None)
			{
				int8_t posidentity = pos.x;
				InsertBytes(ret, posidentity);
			}
			else
			{
				InsertBytes(ret, pos.x);

			}
			if ((cubeflags & CubeFlags::PosY_8b) != CubeFlags::None)
			{
				int8_t posidentity = pos.y;
				InsertBytes(ret, posidentity);
			}
			else
			{
				InsertBytes(ret, pos.y);

			}
			if ((cubeflags & CubeFlags::PosZ_8b) != CubeFlags::None)
			{
				int8_t posidentity = pos.z;
				InsertBytes(ret, posidentity);
			}
			else
			{
				InsertBytes(ret, pos.z);

			}
		}
		if ((cubeflags & CubeFlags::BaseMaterial) != CubeFlags::None)
		{
			InsertBytes(ret, cubeinfo.materials[0]);

		}
		else
		{
			InsertBytes(ret, cubeinfo.materials);

		}
		if ((cubeflags & CubeFlags::IdentityByteCorners) == CubeFlags::None)
		{
			InsertBytes(ret, cubeinfo.corners);
		}

	}
	return ret;
}

Model Model::FromBytes(std::vector<byte>& bytes)
{
	auto ret = Model();
	size_t i = 0;
	while (i < bytes.size())
	{
		auto flags = GetValueFromBytes<CubeFlags>(bytes, i++);
		i16Vector pos{};
		CubeInfo cubeinfo{};
		if ((flags & CubeFlags::PosIdentity) != CubeFlags::None )
		{
			if ((flags & CubeFlags::PosX_8b) != CubeFlags::None)
			{
				pos.x = GetValueFromBytes<int8_t>(bytes,i++);
			}
			else
			{
				pos.x = GetValueFromBytes<int16_t>(bytes, i);
				i += 2;

			}
			pos.y = pos.x;
			pos.z = pos.x;
		}
		else
		{
			if ((flags & CubeFlags::PosX_8b) != CubeFlags::None)
			{
				pos.x = GetValueFromBytes<int8_t>(bytes, i++);
			}
			else
			{
				pos.x = GetValueFromBytes<int16_t>(bytes, i++);
				i += 2;
			}
			if ((flags & CubeFlags::PosY_8b) != CubeFlags::None)
			{
				pos.y = GetValueFromBytes<int8_t>(bytes, i++);
			}
			else
			{
				pos.y = GetValueFromBytes<int16_t>(bytes, i++);
				i += 2;
			}
			if ((flags & CubeFlags::PosZ_8b) != CubeFlags::None)
			{
				pos.z = GetValueFromBytes<int8_t>(bytes, i++);
			}
			else
			{
				pos.z = GetValueFromBytes<int16_t>(bytes, i++);
				i += 2;
			}
		}

		if ((flags & CubeFlags::BaseMaterial) != CubeFlags::None)
		{
			cubeinfo.materials = cubeinfo.CreateMaterials(GetValueFromBytes<byte>(bytes, i++));
		}
		else
		{
			cubeinfo.materials = GetValueFromBytes<MaterialsInfo>(bytes, i);
			i += 6;
		}

		if ((flags & CubeFlags::IdentityByteCorners) == CubeFlags::None)
		{
			cubeinfo.corners = GetValueFromBytes<CornersInfo>(bytes, i);
			i += 8;
		}

		ret.AddCube(pos, cubeinfo);
	}
	return ret;
}

CubeFlags Model::GetFlags(const i16Vector& pos, CubeInfo& cubeinfo)
{
	CubeFlags ret = CubeFlags::None;
	auto posxis8bit = UtilsInt::Is8bit(pos.x);
	auto posyis8bit = UtilsInt::Is8bit(pos.y);
	auto poszis8bit = UtilsInt::Is8bit(pos.z);
	auto pos_isidentity = pos.x == pos.y && pos.x == pos.z;
	auto cube_isbasematerials = cubeinfo.IsBaseMaterials();
	auto cubeisidentity = cubeinfo.IsIdentityByteCorners();
	if (cube_isbasematerials) ret |= CubeFlags::BaseMaterial;
	if (cubeisidentity) ret |= CubeFlags::IdentityByteCorners;
	if (posxis8bit) ret |= CubeFlags::PosX_8b;
	if (posyis8bit) ret |= CubeFlags::PosY_8b;
	if (poszis8bit) ret |= CubeFlags::PosZ_8b;
	if (pos_isidentity) ret |= CubeFlags::PosIdentity;

	return ret;
}


