#include <iostream>
#include "Model.h"
#include <fstream>

static std::vector<byte> readFile(const char* filename)
{
    std::ifstream file(filename, std::ios::binary);
    file.unsetf(std::ios::skipws);


    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<byte> vec;
    vec.reserve(fileSize);

    vec.insert(vec.begin(),
        std::istream_iterator<byte>(file),
        std::istream_iterator<byte>());
    file.close();
    return vec;
}
static void Test1()
{
    std::ofstream myoutfile("data.dat", std::ios_base::binary | std::ios_base::out);
    Model mymodel;
    mymodel.AddCube({ -1,-1,-1 }, CubeInfo(1));

    auto result = mymodel.ToBytes();
    myoutfile.write((char*)result.data(), result.size());
    myoutfile.close();
}
static void Test2()
{
    auto bytes = readFile("data.dat");
    Model mymodel = Model::FromBytes(bytes);
    for (auto& key_val : mymodel.cubesinfo)
    {
        auto pos = key_val.first;
        std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
    }
}

int main()
{
    Test1();
    Test2();
}