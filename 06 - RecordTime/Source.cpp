#include <iostream>
#include <chrono>

int DoSomeLongRunningThing()
{
    int counter = 0;
    for (int i = 0; i < 9000; i++)
    {
        std::cout << " " << std::endl;
        counter += 1;
    }
    return counter;
}

// Template to pass any function without args.
// Return the time taken to run the passed function
template <typename returnT>
double timeTaken(returnT (*funcToRun) (void))
{
    auto startTime = std::chrono::steady_clock::now();

    // Run the function
    funcToRun();

    auto endTime = std::chrono::steady_clock::now();
    // Get the diference in time and return it
    std::chrono::duration<double> timeDiff = endTime - startTime;
    return timeDiff.count();
}


int main(int argc, char** argv)
{
    // Determine the time taken to print "Hello World"
    {
        auto startTime = std::chrono::steady_clock::now();
        
        std::cout << "Hello World" << std::endl;
        
        auto endTime = std::chrono::steady_clock::now();
        // Get the diference in time, and display it
        std::chrono::duration<double> timeDiff = endTime - startTime;
        std::cout << "Seconds elapsed: " << timeDiff.count() << std::endl;
    }


    // Pass the function as a function pointer, then display the time taken
    double execTime = timeTaken(DoSomeLongRunningThing);
    std::cout << "Seconds elapsed: " << execTime << std::endl;
}