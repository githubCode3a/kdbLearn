This repository shows how to import JSON object (from [UniBit](https://unibit.ai) API request) into kdb+ (via c++, pyq).

```./q/l64/q -p 12345```

```cd UniBit```

```clear && printf '\e[3J'; rm UniBit; g++ -DKXVER=3 -o -std=c++11 -o UniBit include/internal/*.cpp UniBit.cpp c.o -lpthread -lboost_system -lcrypto -lssl -lcpprest; ./UniBit >> log.log```


Files can be found in quotes/{ticker}.csv

Log information can be checked via UniBit/log.log (intermittent logs).

---
Prerequisites

You have to install ```nlohmann/json.hpp``` and ```cpprest``` (Microsoft).
