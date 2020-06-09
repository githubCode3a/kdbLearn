// https://github.com/nlohmann/json/tree/develop/doc/examples
// clear && printf '\e[3J';  g++ -DJSON_MultipleHeaders=ON -DKXVER=3 -o jsonREADME jsonREADME.cpp c.o -lpthread; ./jsonREADME
#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp> // https://packages.debian.org/stretch/all/nlohmann-json-dev/download
// and check installation via https://www.thelinuxfaq.com/ubuntu/ubuntu-17-04-zesty-zapus/nlohmann-json-dev

using json = nlohmann::json;

int main()
{
    // create a JSON object
    json j =
    {
        {"pi", 3.141},
        {"happy", true},
        {"name", "Niels"},
        {"nothing", nullptr},
        {
            "answer", {
                {"everything", 42}
            }
        },
        {"list", {1, 0, 2}},
        {
            "object", {
                {"currency", "USD"},
                {"value", 42.99}
            }
        }
    };

    // add new values
    j["new"]["key"]["value"] = {"another", "list"};

    // count elements
    auto s = j.size();
    j["size"] = s;

    // pretty print with indent of 4 spaces
    std::cout << std::setw(4) << j << '\n';
}