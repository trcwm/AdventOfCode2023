// Day4 part 1
#include <iostream>
#include <string>
#include <string_view>
#include <iostream>
#include <fstream>
#include <array>
#include <stdexcept>
#include <vector>
#include <unordered_set>

std::vector<std::string>
    split(const std::string &str, std::string_view delims = " ")
{
    std::vector<std::string> result;
    result.reserve(20);

    std::size_t idx = 0;
    while(idx < str.size())
    {
        auto const endIdx = str.find_first_of(delims, idx);

        if (idx != endIdx)
        {
            result.emplace_back(str.substr(idx, endIdx - idx));
        }

        if (endIdx == std::string_view::npos)
            break;

        char delim = str.at(endIdx);
        if (delim != ' ')
        {
            std::string delimStr(1, delim);
            result.emplace_back(delimStr);
        }
        idx = endIdx + 1;
    }

    return result;
}

int main(const int argc, const char *argv[])
{
    std::ifstream data("input.txt");

    if (!data.is_open())
    {
        std::cerr << "Cannot open input.txt!\n";
        return EXIT_FAILURE;
    }

    int sum = 0;
    for (std::string line; std::getline(data, line);)
    {
        auto chunks = split(line, " :|");

        try
        {
            if (chunks.at(0) != "Card")
            {
                continue;
            }

            auto cardID = std::stoi(chunks.at(1));

            auto iter = chunks.begin() + 3;

            std::unordered_set<int> winningSet;
            while(iter != chunks.end())
            {
                if (*iter == "|") break;

                auto winningNumber = std::stoi(*iter);
                iter++;                
                winningSet.insert(winningNumber);

                if (iter == chunks.end())
                {
                    std::cerr << "Unexpected end of line\n";
                    return EXIT_FAILURE;
                }
            }

            // check the numbers we have for winners
            iter++;

            int matches = 0;
            while(iter != chunks.end())
            {
                auto drawn = std::stoi(*iter);
                iter++;

                if (winningSet.contains(drawn))
                {
                    matches++;
                }
            }

            if (matches > 0)
            {
                sum += (1<<(matches-1));
            }
            
        }
        catch(std::out_of_range &e)
        {
            std::cerr << e.what() << "\n";
        }
    }

    std::cout << "Sum: "<< sum << "\n";

    return EXIT_SUCCESS;
}
