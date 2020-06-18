This repository shows how to import JSON object (from [UniBit](https://unibit.ai) API request; used to interview with UniBit CEO Vincent Jiang on Jan 16th 2020~ :) ) into kdb+ (via c++, pyq).

```./q/l64/q -p 12345```

```cd UniBit```

```clear && printf '\e[3J'; rm UniBit; g++ -DKXVER=3 -o -std=c++11 -o UniBit include/internal/*.cpp UniBit.cpp c.o -lpthread -lboost_system -lcrypto -lssl -lcpprest; ./UniBit >> log.log```

This imports 3598 US stocks into kdb+ and save as ```{ticker}.csv``` files. Implementation is single-thread and requires 130s (if there is no credit limit on API accounts) or at least within 5 mins.

Files can be found in ```quotes/{ticker}.csv```

Log information can be checked via [```UniBit/log.log```](UniBit/log.log) (intermittent logs).

---
Prerequisites

(1) You have to install ```nlohmann/json.hpp``` and ```cpprest``` (Microsoft).

(2) Ubuntu (```sudo apt install  nlohmann-json3-dev libcpprest-dev```) is recommended rather than Mac OSX (although it has ```brew install nlohmann_json cpprestsdk```).

(3) Thanks [codyfeng](https://github.com/codyfeng/kdb-cpp) for a relatively complete Kdb interface.
