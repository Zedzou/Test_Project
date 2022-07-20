#include <iostream>
#include <map>
#include "Vector"
#include <Eigen/Core>


int main()
{
    std::map<ORUtils::Vector4<int>, int> InstanceID;

    ORUtils::Vector4<int>ColorRGBA (0, 0, 0, 255);
    InstanceID.insert(std::pair<ORUtils::Vector4<int>, int>(ColorRGBA, 1));

    auto iter = InstanceID.find(ColorRGBA);
    if(iter!=InstanceID.end()){
        int i = InstanceID.at(ColorRGBA);
        std::cout << i << std::endl;
    }

    return 0;
}
