//
// Created by cheri on 2024/12/3.
//

#include "Log.h"

#include <iostream>
#include <string>
using namespace std;

void log(std::string str) {
    std::cout << str << endl;
}

namespace TestNameSpace{
    string xiaoyumi = "TestNameSpace_xiaoyumi";
    string xiaoyumi2  = "TestNameSpace_xiaoyumi2";
}

