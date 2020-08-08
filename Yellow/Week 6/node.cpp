// #include "n  ode.h"
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
#include <functional>
#include "database.h"
#include "main.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "token.h"
#include "operators.h"

using namespace std;

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &_log_op, const shared_ptr<Node> &_lhs, const shared_ptr<Node> &_rhs) {
    log_op = _log_op;
    lhs = _lhs;
    rhs = _rhs;
}

DateComparisonNode::DateComparisonNode(const Comparison &_cmp, const Date &_date) {
    cmp = _cmp;
    date = _date;
}

bool LogicalOperationNode::Evaluate(const Date& date, const string &event) const {
    return log_op == LogicalOperation::Or ? lhs->Evaluate(date, event) || rhs->Evaluate(date, event)
        : log_op == LogicalOperation::And ? lhs->Evaluate(date, event) && rhs->Evaluate(date, event) : false;
}

bool EventComparisonNode::Evaluate(const Date&date, const string &event) const {
    return Comparator(cmp, event, this->event);
}

bool DateComparisonNode::Evaluate(const Date&date, const string &event) const {
    return Comparator(cmp, date, this->date);
}

bool EmptyNode::Evaluate(const Date& date, const string &event) const {
    return true;
}

template <class T>
bool Comparator(const Comparison &cmp, const T &lhs, const T &rhs) {
    switch (cmp)
    {
    case Comparison::Less:
        return lhs < rhs;
    case Comparison::LessOrEqual:
        return lhs <= rhs;
    case Comparison::Equal:
        return lhs == rhs;
    case Comparison::GreaterOrEqual:
        return lhs >= rhs;
    case Comparison::Greater:
        return lhs > rhs;
    case Comparison::NotEqual:
        return lhs != rhs;
    }
    return false;
}
