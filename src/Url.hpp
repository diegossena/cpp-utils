#include "index.hpp"
class URL
{
public:
  string protocol;
  string host;
  u_short port;
  string path;
  URL(string input)
  {
    unsigned short index1, index2;
    index1 = input.find(':');
    protocol = input.substr(0, index1);
    input = input.substr(index1 + 3);
    index1 = input.find('/');
    index2 = input.find(':');
    index1 = index1 < index2 ? index1 : index2;
    host = input.substr(0, index1);
    if (index1 < input.length())
    {
      input = input.substr(index1);
    }
    if (input[0] == ':')
    {
      port = atoi(input.substr(1, input.find('/')).c_str());
    }
    else
    {
      port = 80u;
    }
    index1 = input.find('/');
    if (index1 < input.length())
    {
      path = input.substr(index1);
    }
    else
    {
      path = '/';
    }
  }
};