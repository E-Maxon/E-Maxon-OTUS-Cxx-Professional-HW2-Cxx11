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

auto filter(const std::vector<std::vector<int> >& ip_pool, bool (*func) (const std::vector<int>&)) {
    std::vector<std::vector<int> > res;
    for (const auto& ip : ip_pool) {
        if (func(ip)) {
            res.push_back(ip);
        }
    }
    return res;
}

std::ostream& operator<<(std::ostream& s, const std::vector<std::vector<int> >& ip_pool) {
    for (const auto& ip : ip_pool) {
        auto first = true;
        for (const auto& number : ip) {
            if (!first) {
                std::cout << ".";
            }
            first = false;
            std::cout << number;
        }
        std::cout << std::endl;
    }
    return s;
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

        std::vector<std::vector<int> > res1;
        for (const auto& ip : ip_pool) {
            res1.push_back({});
            for (const auto& number : ip) {
                res1.back().push_back(std::stoi(number));
            }
        }

        auto comp = [](const std::vector<int>& a,
                       const std::vector<int>& b) {
                            for (auto i = 0; i < a.size() && i < b.size(); i++) {
                                if (a[i] > b[i]) {
                                    return true;
                                } else if (a[i] < b[i]) {
                                    return false;
                                }
                            }
                            return a.size() > b.size();
        };

        sort(res1.begin(), res1.end(), comp);
        std::cout << res1;

        auto f2 = [](const std::vector<int>& ip) {
            return ip[0] == 1;
        };
        auto res2 = filter(res1, f2);
        std::cout << res2;

        auto f3 = [](const std::vector<int>& ip) {
            return ip[0] == 46 && ip[1] == 70;
        };
        auto res3 = filter(res1, f3);
        std::cout << res3;

        auto f4 = [](const std::vector<int>& ip) {
            for (const auto& number : ip) {
                if (number == 46) {
                    return true;
                }
            }
            return false;
        };
        auto res4 = filter(res1, f4);
        std::cout << res4;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
