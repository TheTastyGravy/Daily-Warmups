#include <iostream>


int SharedLetters(std::string str1, std::string str2)
{
    int count = 0;
    bool letterIsDone;


    for (int i = 0; i < str1.length(); i++)
    {
        //check if the letter has been done already
        letterIsDone = false;
        for (int j = 0; j < i; j++)
        {
            if (str1[i] == str1[j])
            {
                letterIsDone = true;
                break;
            }
        }

        if (letterIsDone)
        { continue; }


        //check if letter is shared
        for (int j = 0; j < str2.length(); j++)
        {
            if (str1[i] == str2[j])
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
    std::cout << SharedLetters("apple", "meaty") << std::endl; //2
    std::cout << SharedLetters("fan", "forsook") << std::endl; //1
    std::cout << SharedLetters("spout", "shout") << std::endl; //4

    return 0;
}