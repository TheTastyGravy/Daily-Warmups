#include <iostream>
#include <vector>


std::vector<std::string> splitGroups(const std::string& s)
{
    using std::string;
    std::vector<string> result;

    // Dont run if the string is empty
    if (s.empty())
        return result;

    // Add the first char
    result.push_back(string(1, s[0]));
    bool first = true;


    for (auto i : s)
    {
        // Lazy skip first char
        if (first)
        {
            first = false;
            continue;
        }


        // Look at the first char of the last element
        if (result.back()[0] == i)
        {
            // Append the char onto the string
            result.back().append(1, i);
        }
        else
        {
            // Add new element to 'result'
            result.push_back(string(1, i));
        }
    }

    return result;
}


void print(std::vector<std::string> vec)
{
    for (auto i : vec)
    {
        std::cout << i.c_str() << std::endl;
    }

    std::cout << std::endl;
}

int main()
{
    print(splitGroups("555"));                 //["555"]
    print(splitGroups("5556667788"));          //["555", "666", "77", "88"]
    print(splitGroups("aaabbbaabbab"));        //["aaa", "bbb", "aa", "bb", "a", "b"]
    print(splitGroups("abbbcc88999&&!!!_"));   //["a", "bbb", "cc", "88", "999", "&&", "!!!", "_"]
}