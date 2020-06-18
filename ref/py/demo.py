# https://github.com/polygon-io/client-python
import time
import pandas as pd
import  pyq
from datetime import date
from polygon import WebSocketClient, STOCKS_CLUSTER
import numpy as np

if __name__ == "__main__":
    df = pd.read_csv("~/github/kdbLearn/companylist.csv")
    
    # c=pyq.q.conn(host="127.0.0.1",port=12345)
    # print(c('1+1'))
    # print(dir(q))
    print("=============")
    # pyq.q.symbols.show()
    pyq.q("\l /home/acer/github/kdbLearn/companylist")
    pyq.q("getallsymbols:{select Symbol from symbols}")
    # pyq.q("getallsymbols:{select Symbol from symbols where Symbol=`MSFT}")
    x = pyq.q.getallsymbols()
    # x.show()

    for name in x:
        # name.show()
        # print(name, type(name))
        # print(name.Symbol, type(name.Symbol))
        sym = str(name.Symbol)
        print(sym, type(sym))
        
    # print("type(x)", type(x))
    # print(list(x))

