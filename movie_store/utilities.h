#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <limits>
#include <sstream>
#include <map>
#include "Howard_Hinnant/include/date/date.h"
using namespace date;
using namespace std::chrono; //pollutes the entire namespace for the program but it's ok, and way easier than dealing wi chrono and date types



//-------------------------general-----------------------------
bool is_num(int& input);
bool is_num(double& input);
bool yes_no();
