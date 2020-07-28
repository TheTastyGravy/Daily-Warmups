#include <iostream>
#include <vector>


bool overTwentyOne(std::vector<char> cards)
{
	int total = 0;

	for (auto card : cards)
	{
		// Number card
		if (isdigit(card))
		{
			total += card - '0';
		}

		// Ace/face card
		if (isalpha(card))
		{
			// Face card
			if (card == 'J' || card == 'K' || card == 'Q')
			{
				total += 10;
			}

			// Ace
			if (card == 'A')
			{
				total += 1;
				//total += (total + 11 > 21) ? 1 : 11;
			}
		}
	}
	
	return total > 21;
}

bool isWinning(std::vector<char> cards)
{
	int total = 0;
	bool hasAce = false;

	for (auto card : cards)
	{
		// Number card
		if (isdigit(card))
		{
			total += card - '0';
		}

		// Ace/face card
		if (isalpha(card))
		{
			// Face card
			if (card == 'J' || card == 'K' || card == 'Q')
			{
				total += 10;
			}

			// Ace
			if (card == 'A')
			{
				total += 1;
				hasAce = true;
			}
		}
	}

	// Winning cards
	if (total == 21)
	{
		return true;
	}
	// If there was an ace, try using 11 instead of 1
	if (hasAce)
	{
		return (total + 10 == 21);
	}
	// Over/under 21
	return false;
}


#define PRINT(x) std::cout << x << std::endl;
int main()
{
	PRINT(overTwentyOne({ '2', '8', 'J' }));			// False
	PRINT(overTwentyOne({ 'A', 'J', 'K' }));			// False
	PRINT(overTwentyOne({ '5', '5', '3', '9' }));		// True
	PRINT(overTwentyOne({ '2', '6', '4', '4', '5' }));	// False
	PRINT(overTwentyOne({ 'J', 'Q', 'K' }));			// True
}