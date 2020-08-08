#pragma once

#include "main.h"
#include "condition_parser.h"
#include "database.h"
#include "token.h"
#include "operators.h"

using namespace std;

enum class Comparison;
enum class LogicalOperation;

template <class T>
bool Comparator(const Comparison &cmp, const T &lhs, const T &rhs);

class Node {
public:
    // Node() = default;
    virtual ~Node() = default;
    virtual bool Evaluate(const Date& date, const string &event) const = 0;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation &_log_op, const shared_ptr<Node> &_lhs, const shared_ptr<Node> &_rhs);
    bool Evaluate(const Date& date, const string &event) const;
private:
    LogicalOperation log_op;
    shared_ptr<Node> lhs;
    shared_ptr<Node> rhs;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison &_cmp, const Date &_date);
    bool Evaluate(const Date& date, const string &event) const override;
private:
    Comparison cmp;
    Date date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison &_cmp, const string _event) {
        cmp = _cmp;
        event = _event;
    }
    bool Evaluate(const Date& date, const string &event) const override;
private:
    Comparison cmp;
    string event;
};

class EmptyNode : public Node {
    // EmptyNode();
public:
    ~EmptyNode() = default;
    bool Evaluate(const Date& date, const string &event) const;
};
