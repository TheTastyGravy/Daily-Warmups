#include <iostream>
#include <functional>


// Generates Fibinacci sequence up to 'num', and returns sum of all even numbers
int GenerateFib(const int num)
{
    // Use a recursive lambda
    std::function<int(const int, const int&, const int&)> func = [&func](const int max, const int& n2, const int& n1) -> int
    {
        // n = n-1 + n-2
        int current = n1 + n2;
        int total = 0;
        
        // Dont go over max
        if (current <= max)
        {
            // If even, add to total
            if (current % 2 == 0)
                total += current;
            
            // Get the next number in the sequence
            total += func(max, n1, current);
        }


        return total;
    };


    // Return the result
    return func(num, 0, 1);
}


int main(int argc, char** argv)
{
    std::cout << GenerateFib(13) << std::endl; // 10 = 2 + 8
    std::cout << GenerateFib(17) << std::endl; // 10 = 2 + 8
    std::cout << GenerateFib(45) << std::endl; // 44 = 2 + 8 + 34
    std::cout << GenerateFib(55) << std::endl; // 44 = 2 + 8 + 34
}