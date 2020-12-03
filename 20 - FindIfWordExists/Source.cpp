#include <iostream>
#include <fstream>
#include <string>


bool FindWord(const std::string& word, std::ifstream* file, int lineCount)
{
    std::string str;

    bool found = false;

    int min = 0;
    int max = lineCount;
    //go to start of file
    int i = 0;
    file->seekg(0);

    do
    {
        int mid = min + (max - min) / 2;

        //move to mid line

        if (i < mid)
        {
            char c;

            while (i < mid)
            {
                file->get(c);
                
                while (c != '\n')
                {
                    file->get(c);
                }
                
                i++;
            }
        }
        else
        {
            char c = 'a';

            while (i > mid-1)
            {
                while (c != '\n')
                {
                    //get prev char
                    file->seekg((std::ios::streamoff)(-1), std::ios::cur);
                    file->get(c);
                    file->seekg((std::ios::streamoff)(-1), std::ios::cur);
                }

                file->seekg((std::ios::streamoff)(-2), std::ios::cur);
                file->get(c);
                file->seekg((std::ios::streamoff)(-2), std::ios::cur);
                
                i--;
            }
            file->seekg(4, std::ios::cur);
            i++;
        }

        std::getline(*file, str);
        i++;
        

        int strComp = word.compare(str);
        
        if (strComp == 0)
        {
            found = true;
        }
        else if (strComp < 0)
        {
            //reset file pos to avoid going backward
            file->seekg(0);
            i = 0;

            max = mid;
        }
        else if (strComp > 0)
        {
            min = mid;
        }

        //not found
        if (min == max-1)
        {
            break;
        }

    } while (!found);

    
    return found;
}

std::ifstream* loadFile(int& count)
{
    //open file
    std::ifstream* file = new std::ifstream();
    file->open("words_alpha.txt");

    if (!file->is_open())
    {
        std::cout << "Failed to open file" << std::endl;
        return nullptr;
    }


    //count new lines in file
    count = std::count(std::istreambuf_iterator<char>(*file),
        std::istreambuf_iterator<char>(), '\n');



    return file;
}


int main(int argc, char** argv)
{
    int count;
    std::ifstream* file = loadFile(count);


    // FOUND
    std::cout << "abacination:" << (FindWord("abacination", file, count) ? "found" : "not found") << std::endl;

    // FOUND
    std::cout << "palaeodictyopterous:" << (FindWord("palaeodictyopterous", file, count) ? "found" : "not found") << std::endl;

    // FOUND
    std::cout << "hello:" << (FindWord("hello", file, count) ? "found" : "not found") << std::endl;

    // NOT FOUND
    std::cout << "fliberty:" << (FindWord("fliberty", file, count) ? "found" : "not found") << std::endl;

    // NOT FOUND
    std::cout << "z:" << (FindWord("z", file, count) ? "found" : "not found") << std::endl;


    file->close();
    return 0;
}