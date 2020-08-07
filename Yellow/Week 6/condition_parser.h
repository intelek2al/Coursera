#pragma once

#include "main.h"
// #include "node.h"
// #include "date.h"
// #include <memory>
// #include <iostream>

using namespace std;

// void TestParseCondition();

class Node;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};


shared_ptr<Node> ParseCondition(istream& is);

