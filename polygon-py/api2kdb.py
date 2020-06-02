# https://github.com/polygon-io/client-python
import time
import pandas as pd
import pyq
from datetime import date
from polygon import WebSocketClient, STOCKS_CLUSTER
import datetime
# https://stackoverflow.com/questions/47604139/python-get-all-dates-within-an-interval
import pendulum
from polygon import RESTClient



class key2client:
    # # https://github.com/polygon-io/client-python/blob/master/polygon/websocket/websocket_client.py
    # def my_customer_process_message(self, message):
    #     print("this is my custom message processing", message)
    def __init__(self, key = 'aGls_e4_gw0XgXU_XY64XFrrP88o_tcQ3qmYWY'):
        
        # self.my_client = WebSocketClient(STOCKS_CLUSTER, key, self.my_customer_process_message)
        # self.my_client.run_async()
        self.RESTclient = RESTClient(key)

        
        
    # def subscribe(self):
    #     self.my_client.subscribe("T.MSFT", "T.AAPL", "T.AMD", "T.NVDA")


        
    
    # https://github.com/polygon-io/client-python/blob/master/rest-example.py
    def query(self, sym,time_str):#"AAPL", "2018-3-2"
        # sym, time_str = "AAPL", "2018-3-2"
        # client = RESTClient(key)
        resp = None
        try:
            resp = self.RESTclient.stocks_equities_daily_open_close(sym,time_str)
            print(f"On: {resp.from_}\t{sym} opened at {resp.open} and closed at {resp.close}")
        except:
            pass
        # time.sleep(2)
        return resp

    # def __del__(self):
    #     self.my_client.close_connection()

if __name__ == "__main__":
    # df = pd.read_csv("~/github/kdbLearn/companylist.csv")
    
    # c=pyq.q.conn(host="127.0.0.1",port=12345)
    # print(c('1+1'))
    # print(dir(q))
    
    # pyq.q.symbols.show()
    pyq.q("\l /home/acer/github/kdbLearn/companylist")
    pyq.q("getallsymbols:{select Symbol from symbols}")
    x = pyq.q.getallsymbols()

    
    x.show()
    # print("type(x)", type(x))
    # print(list(x))

    myClient = key2client()
    # myClient.subscribe()

    #------------------
    # https://stackoverflow.com/questions/47604139/python-get-all-dates-within-an-interval

    # start = pendulum.Pendulum(2019, 12, 30)
    # end = pendulum.Pendulum(2019, 12, 31)
    
    # period = pendulum.period(start, end)
    # period = pendulum.period(start, end)
    #-----------------
    start = pd.to_datetime('December 1, 2017')
    end = pd.to_datetime('June 1, 2018')

    print("=============")
    # Get first day of every month:

    dateLst = pd.date_range(start, end, freq='MS').strftime('%Y-%m-%d').tolist()

    print("dateLst", dateLst)
    i = 0
    for name in x:
        i+=1
        sym = str(name.Symbol)  
        if i>>3:
            break
        print(sym, type(name.Symbol))
            # name.show()
        
        for date_str in dateLst:
            # print(sym, type(sym))
            resp = myClient.query(sym, date_str)
            if resp is not None:
                query = f"`quotes upsert (`{sym};{date_str};{resp.open}e;{resp.close}e;1.{resp.close}e)"
    pyq.q()
    pyq.q("`:/home/acer/github/kdbLearn/companylist dsave `symbols`quotes")
    # pyq.q("`:/home/acer/github/kdbLearn/companylist dsave `symbols")
    