#include <iostream>

using namespace std;

int main()
{
    string source_str;
    string result_str;
    cin >> source_str;
    for (auto symbol : source_str)
    {
        if (!result_str.empty() && symbol == result_str.back())
        {
            result_str.pop_back();
        }
        else
        {
            result_str.push_back(symbol);
        }
    }
    cout << result_str << '\n';

    return 0;
}