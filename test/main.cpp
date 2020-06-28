
#include <cassert>

#include <ensemble/array.hpp>

using Ensemble::Array;

int main()
{
    auto a = Array<std::string>();
    assert(a.Count() == 0);

    auto s1 = std::string();
    a.Append(s1);
    assert(a.Count() == 1);

    auto i = a[0];
    assert(i == s1);
}
