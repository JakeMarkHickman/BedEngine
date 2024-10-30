#pragma once

#include <regex>

namespace Bed
{
    class StringSearcher
    {
    public:
        //Disjunction: (x|y) matches either "x" or "y"
        static std::string Disjunction(std::string* strings, int size);

        //Lookahead assertion: (x(?=y)) only matches "x" if "y" follows
        static std::string LookaheadAssertion(std::string stringToLookFrom, std::string stringToLookFor);

        //Negative Lookahead assertion: (x(?!y)) only matches "x" if "x" isn't followed by "y"
        static std::string NegativeLookaheadAssertion(std::string stringToLookFrom, std::string stringToLookFor);

        //Lookbehind assertion: ((?<=y)x) matches "x" only if "x" follows "y"
        static std::string LookbehindAssertion(std::string stringToLookFrom, std::string stringToLookFor);

        //Negative Lookbehind assertion: ((?<!y)x) matches "x" only if "x" doesn't follow "y"
        static std::string NegativeLookbehindAssertion(std::string stringToLookFrom, std::string stringToLookFor);
    };
}