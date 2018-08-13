#ifndef STRINGIO_H
#define STRINGIO_H
#include "string.h"
#include <iostream>

std::ostream& operator<<(std::ostream& out, const String &xs)
{   if(!xs.null())
    {   out << xs.head();
        out << xs.body();
    }
    return out;
}
std::istream& getline(std::istream& in, String &xs, const char &prd)
{   xs.clear();
    char c;
    in.get(c);
    while(in.good() && c != prd)
        {xs.append(c); in.get(c);}
    return in;
}
std::istream& getline(std::istream& in, String &xs)
    {return getline(in, xs, '\n');}
std::istream& operator>>(std::istream& in, String &xs)
    {return getline(in, xs, '\n');}
#endif