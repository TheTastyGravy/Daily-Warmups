#include <iostream>


bool isValidHexCode(std::string str)
{
    // Must be 7 long and start with a #
    if (str.length() != 7 || str[0] != '#')
    {
        return false;
    }

    // For each char after the #
    for (int i = 1; i < 7; i++)
    {
        // 0-9 is valid
        if (isdigit(str[i]))
            continue;
        
        // a-f is valid
        if (toupper(str[i]) >= 'A' && toupper(str[i]) <= 'F')
            continue;
        
        // Anything else is invalid
        return false;
    }

    // If loop finished, all chars are valid
    return true;
}


#define PRINT(x) std::cout << x <<std::endl;

int main()
{
     PRINT(isValidHexCode("#CD5C5C"));     //true
     PRINT(isValidHexCode("#EAECEE"));     //true
     PRINT(isValidHexCode("#eaecee"));     //true
     PRINT(isValidHexCode("#CD5C58C"));    //false  Length exceeds 6
     PRINT(isValidHexCode("#CD5C5Z"));     //false  Not all alphabetic characters in A-F
     PRINT(isValidHexCode("#CD5C&C"));     //false  Contains unacceptable character
     PRINT(isValidHexCode("CD5C5C"));      //false  Missing #
}