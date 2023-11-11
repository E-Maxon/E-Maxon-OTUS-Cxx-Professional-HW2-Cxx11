#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

auto split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main()
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        auto comp_bytes = [](const std::vector<std::string>& a,
                            const std::vector<std::string>& b) {

                                auto to_bytes = [](const std::string& str) {
                                    return std::stoi(std::bitset<8>(std::stoi(str)).to_string());
                                };
                                for (std::string::size_type i = 0; i < a.size() && i < b.size(); i++) {
                                    if (to_bytes(a[i]) > to_bytes(b[i])) {
                                        return true;
                                    } else if (to_bytes(a[i]) < to_bytes(b[i])) {
                                        return false;
                                    }
                                }
                                return a.size() > b.size();
        };

        sort(ip_pool.begin(), ip_pool.end(), comp_bytes);

        for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
