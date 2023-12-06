// Day2 part 1
#include <iostream>
#include <string>
#include <string_view>
#include <iostream>
#include <fstream>
#include <array>
#include <stdexcept>
#include <vector>

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

struct Draw
{
    int m_red{0};
    int m_green{0};
    int m_blue{0};

    bool operator>(const Draw &max) const
    {
        return (m_red > max.m_red) ||
            (m_green > max.m_green) ||
            (m_blue > max.m_blue);
    }
};

struct Game
{
    int m_id{-1};
    std::vector<Draw> m_draws;

    bool operator>(const Draw &max) const
    {
        for(auto draw : m_draws)
        {
            if (draw > max) return true;
        }
        return false;
    }
};

int main(const int argc, const char *argv[])
{
    std::ifstream data("input.txt");

    if (!data.is_open())
    {
        std::cerr << "Cannot open data.txt!\n";
        return EXIT_FAILURE;
    }

    const std::array<std::string,3> colors =
    {{
        {"red"},
        {"green"},
        {"blue"}
    }};

    std::vector<Game> games;
    games.reserve(100);

    int sum = 0;
    for (std::string line; std::getline(data, line);)
    {
        auto chunks = split(line, " :;,");

        try
        {
            if (chunks.at(0) != "Game")
            {
                continue;
            }

            auto gameID = std::stoi(chunks.at(1));

            auto &game = games.emplace_back();
            game.m_id = gameID;
            game.m_draws.emplace_back();

            auto iter = chunks.begin() + 3;

            while(iter != chunks.end())
            {
                auto count = std::stoi(*iter);
                iter++;
                
                if (iter == chunks.end())
                {
                    std::cerr << "Unexpected end of line\n";
                    return EXIT_FAILURE;
                }

                auto color = *iter++;

                if (color == "red")
                {
                    game.m_draws.back().m_red = count;
                }
                else if (color == "green")
                {
                    game.m_draws.back().m_green = count;
                }
                else if (color == "blue")
                {
                    game.m_draws.back().m_blue = count;
                }
                else
                {
                    std::cerr << "Expected a color name\n";
                    return EXIT_FAILURE;
                }

                // check if we have a ';' or ',' delimiter
                if (iter != chunks.end())                
                {
                    if (*iter == ";")
                    {
                        game.m_draws.emplace_back(); // create new draw.
                        iter++;
                    }
                    else if (*iter == ",")
                    {
                        iter++;
                    }
                    else
                    {
                        std::cerr << "Unexpected input '" << *iter << "'\n";
                        return EXIT_FAILURE;
                    }
                }
            }

            //std::cout << "\n";
        }
        catch(std::out_of_range &e)
        {
            std::cerr << e.what() << "\n";
        }
    }

    // check which games are possible
    // with 12 red cubes, 13 green cubes, and 14 blue cubes.
    auto maxDraw = Draw{.m_red = 12, .m_green = 13, .m_blue = 14};

    for(int idx = 0; idx < games.size(); idx++)
    {
        if (!(games.at(idx) > maxDraw))
        {
            sum += games.at(idx).m_id;
        }
    }

    std::cout << "Sum: "<< sum << "\n";

    return EXIT_SUCCESS;
}
