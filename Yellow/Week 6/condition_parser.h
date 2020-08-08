#pragma once

#include "main.h"
#include "database.h"
#include "token.h"
#include "operators.h"
#include "node.h"

using namespace std;

void TestParseCondition();

class Node;

enum class Comparison
{
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation
{
    Or,
    And
};

shared_ptr<Node> ParseCondition(istream &is);
