#include "catch.hpp"

#include "../include/detail/algorithm.hpp"
#include "../include/set_match.hpp"

#include <iterator>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

TEST_CASE("set_match")
{
    struct NumberWithChar
    {
        int number;
        char numberChar;
        bool operator<(NumberWithChar const& other) const {return number < other.number; }
        bool operator==(NumberWithChar const& other) const {return number == other.number; }
    };
    struct NumberWithString
    {
        int number;
        std::string numberName;
        bool operator<(NumberWithString const& other) const {return number < other.number; }
        bool operator==(NumberWithString const& other) const {return number == other.number; }
    };
    std::set<NumberWithChar> input1 = {{1,'1'}, {2,'2'}, {3,'3'}, {5,'5'}, {7,'7'}, {8, '8'}};
    std::set<NumberWithString> input2 = {{2,"two"}, {3,"three"}, {4,"four"}, {5,"five"}, {7,"seven"}, {11,"eleven"}};
    
    std::vector<std::pair<NumberWithChar,NumberWithString>> expected = { { {2,'2'}, {2,"two"}   },
        { {3,'3'}, {3,"three"} },
        { {5,'5'}, {5,"five"}  },
        { {7,'7'}, {7,"seven"} } };
    
    std::vector<std::pair<NumberWithChar,NumberWithString>> results;
    struct NumberCharStringCompare
    {
        bool operator()(NumberWithChar const& numberWithChar, NumberWithString const& numberWithString) { return numberWithChar.number < numberWithString.number; }
        bool operator()(NumberWithString const& numberWithString, NumberWithChar const& numberWithChar) { return numberWithString.number < numberWithChar.number; }
    };
    
    fluent::set_match(input1, input2, std::back_inserter(results), NumberCharStringCompare());
    
    REQUIRE(results == expected);
}

TEST_CASE("set_match with map")
{
    std::map<int, char> input1 = {{1,'1'}, {2,'2'}, {3,'3'}, {5,'5'}, {7,'7'}, {8, '8'}};
    std::map<int, std::string> input2 = {{2,"two"}, {3,"three"}, {4,"four"}, {5,"five"}, {7,"seven"}, {11,"eleven"}};
    
    std::vector<std::pair<std::pair<int, char>, std::pair<int, std::string>>> expected =
      { { {2,'2'}, {2,"two"}   },
        { {3,'3'}, {3,"three"} },
        { {5,'5'}, {5,"five"}  },
        { {7,'7'}, {7,"seven"} } };
    
    std::vector<std::pair<std::pair<int, char>, std::pair<int, std::string>>> results;
    struct NumberCharStringCompare
    {
        bool operator()(std::pair<int, char> const& numberWithChar, std::pair<int, std::string> const& numberWithString) { return numberWithChar.first < numberWithString.first; }
        bool operator()(std::pair<int, std::string> const& numberWithString, std::pair<int, char> const& numberWithChar) { return numberWithString.first < numberWithChar.first; }
    };
    
    fluent::set_match(input1, input2, std::back_inserter(results), NumberCharStringCompare());
    
    REQUIRE(results == expected);
}
