/* DSA problems */

#include <iostream>
#include "WeightedQUPC.hpp"
using namespace DynamicConnectivity;

int main(int argc, const char * argv[]) {
    
    WeightedQUPC::Build("TestData/DynamicConnectivity/tinyUF.txt", true);
    WeightedQUPC::Build("TestData/DynamicConnectivity/mediumUF.txt", false);
    WeightedQUPC::Build("TestData/DynamicConnectivity/largeUF.txt", false);
    return 0;
}
