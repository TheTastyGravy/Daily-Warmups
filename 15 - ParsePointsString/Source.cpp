#include <iostream>
#include <string>
#include <vector>

struct Point { int x; int y; };

// From #2
std::vector<std::string> explode(char seperator, const std::string& str)
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


std::vector<Point> ParsePointString(const std::string& sPoints)
{
    // Each point is seperated by a space
    std::vector<std::string> sepPoints = explode(' ', sPoints);
    std::vector<Point> points;

    for (auto& str : sepPoints)
    {
        // The x and y are seperated by a comma
        std::vector<std::string> strPoint = explode(',', str);
        // Cast each value to int and push point to vector
        points.push_back({ std::stoi(strPoint[0]), std::stoi(strPoint[1]) });
    }

    return points;
}


int main()
{
    std::string sPoints = "0,0 -3,-214 187,-422 196,-862 -95,-1044 -461,-1219 -732,-1310 -950,-1338 -1213,-1339";

    auto points = ParsePointString(sPoints);
    for (auto& point : points)
    {
        std::cout << point.x << "\t" << point.y << std::endl;
    }

    return 0;
}