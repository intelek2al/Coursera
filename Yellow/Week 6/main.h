#pragma once

#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <set>
#include <sstream>
#include <tuple>

#include "date.h"
#include "condition_parser.h"
#include "database.h"
#include "node.h"
#include "token.h"
#include "operators.h"

using namespace std;

string ParseEvent(istream &is);
Date ParseDate(istringstream &date_stream);
