#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> Explode(char seperator, const std::string& str)
{
    std::vector<std::string> result;
    // find_first_of() returns the first position of the passed char
    size_t pos = str.find_first_of(seperator);
    size_t lastPos = 0;

    while (pos != std::string::npos)
    {
        // Add sub-string to result, given its not empty
        if (lastPos != pos)
            result.push_back(str.substr(lastPos, pos - lastPos));

        // Get next seperator
        lastPos = pos + 1;
        pos = str.find_first_of(seperator, lastPos);
    }

    // Get the remainder of the string before returning
    result.push_back(str.substr(lastPos));
    return result;
}

int main(int argc, char* argv)
{
    std::cout << "---------------------------------------------------------" << std::endl;
    auto words = Explode(' ', "the quick brown fox jumps over the lazy dog");
    std::cout << "There are: " << words.size() << std::endl << std::endl;
    for (auto& w : words) {
        std::cout << w << std::endl;
    }
    std::cout << "---------------------------------------------------------" << std::endl;

    std::cout << "---------------------------------------------------------" << std::endl;
    auto kvp = Explode('&', "aaa:10&bbb:20ccc:30&&&&&ddd:30");
    std::cout << "There are: " << kvp.size() << std::endl << std::endl;
    for (auto& w : kvp) {
        std::cout << w << std::endl;
    }
    std::cout << "---------------------------------------------------------" << std::endl;

    return 0;
}