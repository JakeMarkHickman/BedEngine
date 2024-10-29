#include "StringSearcher.h"

#include <iostream>

std::string Bed::StringSearcher::LookForString(std::string string[])
{
    for(int i = 0; i < string->size(); i++)
    {
        std::cout << string[i] << std::endl;
        //TODO: Crashes
    }
}