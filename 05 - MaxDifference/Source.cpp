#include <iostream>
#include <vector>


int MaxDifference(const std::vector<int>& numbers)
{
    // Start with the first value
    int min = numbers[0];
    int max = min;

    // Iterate through numbers
    for (const int& num : numbers)
    {
        // Find the smallest and larges numbers
        if (num < min)
            min = num;
        else if (num > max)
            max = num;
    }

    // Return the difference
    return max - min;
}

int MaxDifference2(const std::vector<int>& numbers)
{
    // Start at 0
    int diff = 0;

    // Iterate through numbers after the first
    for (int i = 1; i < numbers.size(); i++)
    {
        // Iterate through numbers before the current number
        for (int j = 0; j < i; j++)
        {
            // Check for a larger diff
            if (diff < (numbers[i] - numbers[j]))
                diff = numbers[i] - numbers[j];
        }
    }

    // Return the largest diff found
    return diff;
}


int main(int argc, char** argv)
{
    std::cout << MaxDifference({ 10, 15, 12, 8, 7, 31, 8 }) << std::endl; // 31 - 7 = 24
    std::cout << MaxDifference({ 12, 0, 4, 9, 2, 5, 8, 3 }) << std::endl; // 12 - 0 = 12
    std::cout << MaxDifference2({ 10, 15, 12, 8, 7, 31, 2 }) << std::endl; // 32 - 7 = 24 
    std::cout << MaxDifference2({ 12, 0, 4, 9, 2, 5, 8, 3 }) << std::endl; // 9 - 0 = 9 
    std::cout << MaxDifference2({ 12, 13, 14, 5, 6, 7, 8 }) << std::endl; // 8 - 5 = 3
    std::cout << MaxDifference2({ 12, 13, 14, 8, 7, 6, 5 }) << std::endl; // ?? cannot select min or max?
    std::cout << MaxDifference2({ 1, 2, 3, 4, 5, 6, 7, 8 }) << std::endl; // ?? cannot select a min or max?
    return 0;
}