#include <iostream>


int matchClosingBracket(const std::string& str, int loc)
{
    // Invalid cases; returns -1
    if (loc > str.size())
        return -1;
    if (loc < 0)
        return -1;
    if (str[loc] != '[')
        return -1;


    // How many other open brackets have been encountered?
    int bracketDepth = 0;
    // Itterate over everything after the open bracket
    for (int i = loc + 1; i < str.size(); i++)
    {
        // Open bracket, increase depth
        if (str[i] == '[')
        {
            bracketDepth++;
        }
        if (str[i] == ']')
        {
            // Same depth as open bracket, this is its closing bracket
            if (bracketDepth == 0)
                return i;
            // Reduce depth
            else
                bracketDepth--;
        }
    }


    // Closing bracket not found
    return -1;
}


int main()
{
    std::string bf = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.[";

    std::cout << matchClosingBracket(bf, 1) << std::endl;   // -1
    std::cout << matchClosingBracket(bf, 8) << std::endl;   // 48
    std::cout << matchClosingBracket(bf, 14) << std::endl;  // 33
    std::cout << matchClosingBracket(bf, 43) << std::endl;  // 45
    std::cout << matchClosingBracket(bf, 101) << std::endl; // -1
    std::cout << matchClosingBracket(bf, -1) << std::endl;  // -1

    return 0;
}