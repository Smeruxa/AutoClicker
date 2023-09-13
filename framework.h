#pragma once

#define WIN32_LEAN_AND_MEAN

#pragma warning(disable : 4244)

#pragma comment(lib, "comctl32.lib")

#include "targetver.h"
#include <windows.h>
#include <tchar.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <commctrl.h>

#include "include/nlohmann/json.hpp"
#include "Config.h"
#include "clicker.h"