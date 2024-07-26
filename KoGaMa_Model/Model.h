#pragma once
#include "CubeInfo.h"
#include <unordered_map>
#include "CubeFlags.h"
struct Model
{
	std::unordered_map<i16Vector, CubeInfo, i16Vector::KeyHasher> cubesinfo;
	bool AddCube(i16Vector pos, CubeInfo cube);
	bool ReplaceCube(i16Vector pos, CubeInfo cube);
	std::tuple<CubeInfo, bool> GetCube(i16Vector pos);
	bool RemoveCube(i16Vector pos);
	std::vector<byte> ToBytes();
	template<typename T, int Size = sizeof(T), int Offset = 0>
	static void InsertBytes(std::vector<byte>& stream, T& val)
	{
		auto bval = (byte*)&val;
		stream.insert(stream.end(), bval + Offset, bval + Size);
	};
	template<typename T, int Size = sizeof(T), int Offset = 0>
	static T GetValueFromBytes(std::vector<byte>& stream, size_t idx)
	{
		T val{};
		auto sourceval = (stream.size() - idx);
		memcpy_s(&val, Size, stream.data() + idx, sourceval > Size ? Size : sourceval);
		return val;
	};
	static Model FromBytes(std::vector<byte>& bytes);
	static CubeFlags GetFlags(const i16Vector& pos, CubeInfo& cubeinfo);
};