#pragma once

#include "http_request.h"

#include <vector>
#include <string_view>
#include <string>
#include <array>
#include <map>

using namespace std;

#define MTH 5
#define URI 6

class Stats
{
public:
	Stats();
	void AddMethod(string_view method);
	void AddUri(string_view uri);
	const map<string_view, int> &GetMethodStats() const;
	const map<string_view, int> &GetUriStats() const;

private:
	map<string_view, int> methods;
	map<string_view, int> uris;
	array<string, 5> static_methods = {"DELETE", "GET", "POST", "PUT", "UNKNOWN"};
	array<string, 6> static_uri = {"/", "/order", "/product", "/basket", "/help", "unknown"};
};

vector<string_view> SplitIntoWordsView(string_view str, char delim);
HttpRequest ParseRequest(string_view line);
