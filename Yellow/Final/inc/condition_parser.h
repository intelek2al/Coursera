#pragma once

#include "main.h"

using namespace std;

enum class LogicalOperation
{
    And,
    Or
};

enum class Comparison
{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

shared_ptr<Node> ParseCondition(istream &is);

// void TestParseCondition();
