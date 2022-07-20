#include <iostream>
#include "Label_NYU40.h"

int main()
{
    ORUtils::Vector3<int> RGBColor(174, 199, 232);
    auto LabelIdx = NYU40ColorToLabels.at(RGBColor);
    std::cout << LabelIdx << std::endl;

    return 0;
}