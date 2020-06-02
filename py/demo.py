# https://github.com/polygon-io/client-python
import time
import pandas as pd
import  pyq
from datetime import date
from polygon import WebSocketClient, STOCKS_CLUSTER

if __name__ == "__main__":
    df = pd.read_csv("~/github/kdbLearn/companylist.csv")
    
    # c=pyq.q.conn(host="127.0.0.1",port=12345)
    # print(c('1+1'))
    print(dir(q))
    print("=============")
    pyq.q.symbols.show()
    # x = pyq.q.getallsymbols()