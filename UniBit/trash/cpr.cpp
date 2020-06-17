// clear && printf '\e[3J';  g++ -DJSON_MultipleHeaders=ON -DKXVER=3 -o cpr -lcpr cpr.cpp c.o -lpthread; ./cpr
// https://stackoverflow.com/questions/56155428/how-do-i-convert-cprs-get-response-into-a-json-object
// https://github.com/whoshuu/cpr


// CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=/home/acer/github/vcpkg/scripts/buildsystems/vcpkg.cmake"




#include <cpr/cpr.h>

int main(int argc, char** argv) {
    auto r = cpr::Get(cpr::Url{"https://api.unibit.ai/api/realtimestock/AAPL?size=10&AccessKey=demo"},
                      cpr::Authentication{"user", "pass"},
                      cpr::Parameters{{"anon", "true"}, {"key", "value"}});
    r.status_code;                  // 200
    r.header["content-type"];       // application/json; charset=utf-8
    r.text;                         // JSON text string
}