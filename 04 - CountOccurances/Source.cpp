#include <iostream>
#include <string>



int CountOccurances(const std::string& phrase, const std::string& searchTerm)
{
    // If the phrase or search term is empty, it cant have any occurances
    if (phrase.empty() || searchTerm.empty())
        return 0;


    int count = 0;

    // Iterate through the phrase where the term can fit
    for (size_t i = 0; i < phrase.size() - searchTerm.size()+1; i++)
    {
        // Check for the search term
        for (size_t j = 0; true; j++)
        {
            // If they dont match, move on to next char
            if (phrase[i + j] != searchTerm[j])
                break;

            // If the length of the term has been searched without breaking,
            // it must be the term
            if (j == searchTerm.size() - 1)
            {
                count++;
                break;
            }

        }
    }


    return count;
}

int main(int argc, char** argv)
{
    std::string phrase1 = "the quick brown fox jumps over the lazy dog";
    std::string phrase2 = "hello world";
    std::string phrase3 = "aaaaaaaaaaa";
    std::cout << CountOccurances(phrase1, "the") << std::endl;  // -> 2
    std::cout << CountOccurances(phrase1, "o") << std::endl;    // -> 4
    std::cout << CountOccurances(phrase2, "l") << std::endl;    // -> 3
    std::cout << CountOccurances(phrase2, "ll") << std::endl;   // -> 1
    std::cout << CountOccurances(phrase3, "aaa") << std::endl;  // -> 9
    std::cout << CountOccurances(phrase3, "a") << std::endl;    // -> 11

    std::cout << CountOccurances(phrase3, "") << std::endl;   // -> 0
    std::cout << CountOccurances("", "a") << std::endl;   // -> 0

    std::cout << CountOccurances("", "") << std::endl;    // -> ????

    return 0;
}