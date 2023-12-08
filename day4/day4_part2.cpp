// Day4 part 1
#include <iostream>
#include <string>
#include <string_view>
#include <iostream>
#include <fstream>
#include <array>
#include <stdexcept>
#include <vector>
#include <list>
#include <unordered_set>
#include <map>

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

struct Card
{
    int m_id{0};
    std::unordered_set<int> m_numbers;
    std::list<int> m_draws;
};

int countMatches(const Card &card)
{
    int matches = 0;
    for(auto draw : card.m_draws)
    {
        if (card.m_numbers.contains(draw))
        {
            matches++;
        }
    }
    return matches;
}

int main(const int argc, const char *argv[])
{
    std::ifstream data("input.txt");

    if (!data.is_open())
    {
        std::cerr << "Cannot open input.txt!\n";
        return EXIT_FAILURE;
    }

    std::vector<Card> cards;
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

            auto &card = cards.emplace_back();
            card.m_id = cardID;

            auto iter = chunks.begin() + 3;
            while(iter != chunks.end())
            {
                if (*iter == "|") break;

                auto winningNumber = std::stoi(*iter);
                iter++;                
                card.m_numbers.insert(winningNumber);

                if (iter == chunks.end())
                {
                    std::cerr << "Unexpected end of line\n";
                    return EXIT_FAILURE;
                }
            }

            iter++; // skip delimiter

            while(iter != chunks.end())
            {
                auto drawn = std::stoi(*iter);
                iter++;

                card.m_draws.push_back(drawn);
            }
        }
        catch(std::out_of_range &e)
        {
            std::cerr << e.what() << "\n";
        }
    }

    // process cards
    std::map<int /* card ID */, int /* count */> heap;
    for(auto const& card : cards)
    {
        heap[card.m_id]++;
        int matches = countMatches(card);
        int numberOfCards = heap.at(card.m_id);
        for(int m=1; m<=matches; m++)
        {
            heap[card.m_id+m] += numberOfCards;
        }
    }

    // count total number of cards
    for(auto const& card : cards)
    {
        sum += heap.at(card.m_id);
    }

    std::cout << "Sum: "<< sum << "\n";

    return EXIT_SUCCESS;
}
