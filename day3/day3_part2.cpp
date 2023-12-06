// Day1 Part 2
#include <string>
#include <string_view>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using Bitmap = std::vector<std::string>;

bool cellIsSymbol(const Bitmap &bm, int lineNum, int pos)
{
    if ((lineNum < 0) || (pos < 0)) return false;
    if (lineNum >= bm.size()) return false;

    auto const& line = bm.at(lineNum);
    if (pos >= line.size()) return false;

    char cell = line.at(pos);
    if (std::isdigit(cell)) return false;
    if ((cell == '.') || (cell == ' ')) return false;
    return true;
};

struct Number
{
    std::string m_str;
    int         m_value{0};
    int         m_lineNum{-1};
    int         m_pos{-1};
    bool        m_isPartNumber{false};
};

std::list<Number> scanForNumbers(const Bitmap &bm)
{
    std::list<Number> numbers;
    for(std::size_t lineNum = 0; lineNum < bm.size(); lineNum++)
    {
        auto const& line = bm.at(lineNum);
        Number currentNumber;

        for(std::size_t pos = 0; pos < line.size(); pos++)
        {
            char c = line.at(pos);
            if (std::isdigit(c))
            {
                if (currentNumber.m_str.empty())
                {
                    // this is a new number
                    // so store the coordinates
                    currentNumber.m_lineNum = lineNum;
                    currentNumber.m_pos = pos;
                    currentNumber.m_str = c;
                    currentNumber.m_isPartNumber = false;
                }
                else
                {
                    currentNumber.m_str += c;
                }
            }
            else
            {
                if (!currentNumber.m_str.empty())
                {
                    currentNumber.m_value = std::stoi(currentNumber.m_str);
                    numbers.push_back(currentNumber);
                    currentNumber.m_str.clear();
                }
            }
        }

        // push the number if there is one at the
        // end of the line .. 
        if (!currentNumber.m_str.empty())
        {
            currentNumber.m_value = std::stoi(currentNumber.m_str);
            numbers.push_back(currentNumber);
            currentNumber.m_str.clear();
        }        
    }
    return numbers;
}

bool scanForPartNumber(const Bitmap &bm, Number &num)
{
    for(int idx=-1; idx <= static_cast<int>(num.m_str.size()); idx++)
    {
        if (cellIsSymbol(bm,num.m_lineNum-1, num.m_pos+idx)) return true;
        if (cellIsSymbol(bm,num.m_lineNum+1, num.m_pos+idx)) return true;
    }

    if (cellIsSymbol(bm, num.m_lineNum, num.m_pos-1)) return true;
    if (cellIsSymbol(bm, num.m_lineNum, num.m_pos+num.m_str.size())) return true;

    return false;
}

bool isNumberAdjacentTo(const Number &num, int line, int pos)
{
    if ((num.m_lineNum == line) || ((num.m_lineNum-1) == line) || ((num.m_lineNum+1) == line))
    {
        if (((num.m_pos-1) <= pos) && ((num.m_pos+num.m_str.size()) >= pos))
        {
            return true;
        }
    }
    return false;
}

int scanForGears(const Bitmap &bm, const std::list<Number> &numbers)
{
    // slow, but I don't care :)
    int sum = 0;
    int lineNum = 0;
    for(auto const& line : bm)
    {
        int pos = 0;
        for (auto c : line)
        {
            if (c == '*')
            {
                // gear symbol detected
                // but is it really a gear?
                int counter = 0;
                int product = 1;
                for(auto const& num : numbers)
                {
                    if (isNumberAdjacentTo(num, lineNum, pos))
                    {
                        counter++;
                        product *= num.m_value;
                        if (counter >= 2) 
                        {
                            sum += product;
                            break;
                        }
                    }                    
                }
            }
            pos++;
        }
        lineNum++;
    }
    return sum;
}

int main(const int argc, const char *argv[])
{
    std::ifstream data("input.txt");

    if (!data.is_open())
    {
        std::cerr << "Cannot open data.txt!\n";
        return EXIT_FAILURE;
    }

    int sum = 0;
    Bitmap bm;
    for (std::string line; std::getline(data, line);)
    {
        bm.push_back(line);
    }

    auto numbers = scanForNumbers(bm);

    for(auto &num : numbers)
    {
        if (scanForPartNumber(bm, num))
        {
            num.m_isPartNumber = true;
            sum += num.m_value;
        }
    }

    // erase all the non-part numbers
    auto iter = numbers.begin();
    while(iter != numbers.end())
    {
        if (!iter->m_isPartNumber)
        {
            iter = numbers.erase(iter);
        }
        else
        {
            iter++;
        }
    }

    sum  = scanForGears(bm, numbers);
    std::cout << "sum = " << sum << "\n";

    return EXIT_SUCCESS;
}
