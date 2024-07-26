# KoGaMa Model API

It's api for save and load cubes information

# Language 
C++

# Save Model

```cpp
#include <fstream>
#include "Model.h"
int main()
{
	std::ofstream myoutfile("data.dat", std::ios_base::binary | std::ios_base::out);
	Model mymodel;
	mymodel.AddCube({ -1,-1,-1 }, CubeInfo(1));

	auto result = mymodel.ToBytes();
	myoutfile.write((char*)result.data(), result.size());
	myoutfile.close();
}
```

# Load Model

```cpp
#include <fstream>
#include "Model.h"
int main()
{
	auto bytes = readFile("data.dat");
    Model mymodel = Model::FromBytes(bytes);
    for (auto& key_val : mymodel.cubesinfo)
    {
        auto pos = key_val.first;
        std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
    }
}

```