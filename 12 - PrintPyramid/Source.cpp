#include <iostream>


void print_pyramid(int height)
{
    // Iterate up for positive and down for negitive
    int iter = (height > 0) ? 1 : -1;
    // Positive starts at 1, and ends at height
    // Negitive starts at height, and ends at 1
    int start = (height > 0) ? 1 : abs(height);
    int end = (height > 0) ? height+1 : 0;


    for (unsigned int i = start; i != end; i += iter)
    {
        // Print spaces, then stars
        std::cout << std::string((abs(height) - i), ' ') << std::string((2 * i), '*') << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::cout << "=======================================" << std::endl;
    print_pyramid(6);
    std::cout << "=======================================" << std::endl;
    print_pyramid(7);
    std::cout << "=======================================" << std::endl;
    print_pyramid(-1);
    std::cout << "=======================================" << std::endl;
    print_pyramid(-6);
}