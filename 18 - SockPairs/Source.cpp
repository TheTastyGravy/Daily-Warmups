#include <iostream>
#include <functional>
#include <map>


// Returns the number of matching pairs of chars exist in 'socks'
int sockPairs(const std::string& socks)
{
	// Count how many socks of each type there are
	std::map<char, int> counts;
	for (auto sock : socks)
	{
		counts[sock]++;
	}

	// Find the total number of pairs
	int total = 0;
	for (auto& iter : counts)
	{
		// Integer division disreguards fractions
		total += iter.second / 2;
	}


	return total;
}


int main()
{
	std::function<void(int)> print = [](int val)
	{
		std::cout << val << std::endl;
	};

	print(sockPairs("AA"));			// 1
	print(sockPairs("ABABC"));		// 2
	print(sockPairs("CABBACCC"));	// 4
	print(sockPairs("AAAABAAA"));	// 3
	print(sockPairs("ABCDEFG"));	// 0

	return 0;
}