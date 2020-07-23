#include <iostream>
#include <vector>


template<typename T1, typename T2>
struct Pair
{
    T1 first;
    T2 second;
};


template<typename T = int>
T findOdd(const std::vector<T>& arr)
{
    // Store the value and how many times it appears
    std::vector<Pair<T, int>> count;


    // Store the count of each value
    for (auto val : arr)
    {
        bool found = false;

        // Find the value's existing count and increment
        for (auto& pair : count)
        {
            if (pair.first == val)
            {
                pair.second++;
                found = true;
                break;
            }   
        }

        // If not found, add it to count
        if (!found)
        {
            count.push_back({ val, 1 });
        }
    }


    // Return the value that has an odd count
    for (auto val : count)
    {
        if (val.second % 2 == 1)
            return val.first;
    }

    // There was no value that occured an odd number of times
    return NULL;
}


#define PRINT(x) std::cout << x <<std::endl;

int main()
{
    PRINT(findOdd({ 1, 1, 2, -2, 5, 2, 4, 4, -1, -2, 5 })); // return -1
    PRINT(findOdd({ 20, 1, 1, 2, 2, 3, 3, 5, 5, 4, 20, 4, 5 })); // return 5
    PRINT(findOdd({ 10 })); // return 10
}