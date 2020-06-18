#include <iostream>
#include <string>


// Does the first letter of 'str' repeat?
bool doesFirstRepeat(const std::string& str)
{
    // Dont iterate over the first letter
    for (size_t i = 1; i < str.size(); i++)
    {
        // Check if the first letter repeats
        if (str[0] == str[i])
            return true;
    }

    // Loop compleated, so the first letter doesnt repeat
    return false;
}

// Is 'word' an isogram; does it have any repeating letters?
bool isIsogram(std::string word)
{
    // Convert the word to lower case
    for (char& c : word)
        c = tolower(c);
    

    // Iterate through all but last letter
    for (size_t i = 0; i < word.size()-1; i++)
    {
        // If the first letter repeats, its not an isogram
        if (doesFirstRepeat(word.substr(i)))
            return false;
    }

    // If the loop compleated, no letters repeat and the word is an isogram
    return true;
}


int main(int argc, char** argv)
{
    std::cout << "Aaron" << "\t" << isIsogram("Aaron") << std::endl;

    // Random words from a random word generator :P
    std::cout << "Bake" << "\t" << isIsogram("Bake") << std::endl;
    std::cout << "Lay" << "\t" << isIsogram("Lay") << std::endl;
    std::cout << "Issue" << "\t" << isIsogram("Issue") << std::endl;
    std::cout << "Wood" << "\t" << isIsogram("Wood") << std::endl;
    std::cout << "Swop" << "\t" << isIsogram("Swop") << std::endl;
    std::cout << "Coup" << "\t" << isIsogram("Coup") << std::endl;
    std::cout << "Trouser" << "\t" << isIsogram("Trouser") << std::endl;
    std::cout << "Superior" << "\t" << isIsogram("Superior") << std::endl;
    std::cout << "History" << "\t" << isIsogram("History") << std::endl;
    std::cout << "Disclose" << "\t" << isIsogram("Disclose") << std::endl;

    return 0;
}