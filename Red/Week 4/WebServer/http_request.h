#pragma once

#include <string_view>
// #include <array>

using namespace std;

struct HttpRequest
{
  string_view method, uri, protocol;
  // array<string, 3> all;
  HttpRequest(string_view m, string_view u, string_view p)
  {
    // all[0] = m;
    // all[1] = u;
    // all[2] = p;
    // method = all[0];
    // uri = all[1];
    // protocol = all[2];
    method = m;
    uri = u;
    protocol = p;
  }
};
