#include "StringSearcher.h"

std::string Bed::StringSearcher::Disjunction(std::string* strings, int size)
{
    std::string disjunction;

    for(int i = 0; i < size; i++)
    {   
        if (i == size - 1)
        {
            disjunction += strings[i];
        }
        else
        {
            disjunction += strings[i] + "|";
        }
    }

    return disjunction;
}

std::string Bed::StringSearcher::LookaheadAssertion(std::string stringToLookFrom, std::string stringToLookFor)
{
    return stringToLookFrom + "(?=" + stringToLookFor + ")";
}

std::string Bed::StringSearcher::NegativeLookaheadAssertion(std::string stringToLookFrom, std::string stringToLookFor)
{
    return stringToLookFrom + "(?!" + stringToLookFor + ")";
}

std::string Bed::StringSearcher::LookbehindAssertion(std::string stringToLookFrom, std::string stringToLookFor)
{
    return "(?<=" + stringToLookFor + ")" + stringToLookFrom;
}

std::string Bed::StringSearcher::NegativeLookbehindAssertion(std::string stringToLookFrom, std::string stringToLookFor)
{
    return "(?<!" + stringToLookFor + ")" + stringToLookFrom;
}