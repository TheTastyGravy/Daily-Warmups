#include <iostream>
#include <vector>
#include <string>


std::vector<std::string> Explode(char seperator, const std::string& str);

float RPN(const std::string equasion)
{
    using std::string;

    // Split the equation into 'tokens'
    std::vector<string> tokens = Explode(' ', equasion);
    std::vector<int> stack;

    // Loop through each token
    for (string& token : tokens)
    {
        // Int
        try
        {
            // Try to push the int token to stack
            // If it is a symbol, stoi will throw invalid_argument
            stack.push_back(std::stoi(token));
        }
        // Symbol
        catch (std::invalid_argument)
        {
            // There needs to be at least 2 ints for an opperation
            if (stack.size() >= 2)
            {
                // Pop the last 2 values off the stack
                int opp2 = stack.back(); stack.pop_back();
                int opp1 = stack.back(); stack.pop_back();

                int res;

                // Determine what opperation to perform
                if      (token == "+")
                    res = opp1 + opp2;
                else if (token == "-")
                    res = opp1 - opp2;
                else if (token == "/")
                    res = opp1 / opp2;
                else if (token == "*")
                    res = opp1 * opp2;
                else
                    throw "Invalid token";
                
                // Push result
                stack.push_back(res);
            }
            // Less than 2 values on stack
            else
            {
                throw "Not enough values on stack";
            }
        }

        // Remove the token
        token.erase();
    }

    
    // Check the number of values on the stack
    if (stack.size() > 1)
        throw "More than one result on stack";
    else if (stack.size() == 0)
        throw "No result on stack";

    // The remaining value is the result
    return stack[0];
}


int main(int argc, char** argv)
{
    {
        std::string equasion = "10 20 +";
        std::cout << equasion << " = " << RPN(equasion) << "\t\t\tExpected: 30" << std::endl;
    }
    {
        std::string equasion = "10 20 30 + *";
        std::cout << equasion << " = " << RPN(equasion) << "\t\t\tExpected: 500" << std::endl;
    }
    {
        std::string equasion = "20 10 / 4 *";
        std::cout << equasion << " = " << RPN(equasion) << "\t\t\tExpected: 8" << std::endl;
    }
    {
        std::string equasion = "20 10 - 15 +";
        std::cout << equasion << " = " << RPN(equasion) << "\t\t\tExpected: 25" << std::endl;
    }

    return 0;
}


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