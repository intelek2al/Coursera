#pragma once

#include "main.h"

using namespace std;

class Node
{
public:
    Node();
    bool Evaluate(const Date &date, const string &event);
};

class DateComparisonNode : public Node
{
public:
    DateComparisonNode(Comparison &cmp, Date &date)
    {
        this->cmp = cmp;
        this->date = date;
    }

private:
    Comparison cmp;
    Date date;
};

class EmptyNode : public Node
{
public:
    EmptyNode() {}
};

class EventComparisonNode : public Node
{
public:
    EventComparisonNode(Comparison &cmp, string &value)
    {
        this->cmp = cmp;
        this->value = value;
    }

private:
    Comparison cmp;
    string value;
};

class LogicalOperationNode : public Node
{
public:
    LogicalOperationNode(LogicalOperation log_op, Node& lhs, Node& rhs)
    {
        this->log_op = log_op;
        this->lhs = lhs;
        this->rhs = rhs;
    }

private:
    LogicalOperation log_op;
    Node lhs;
    Node rhs;
};
