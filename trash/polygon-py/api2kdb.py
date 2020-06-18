# https://github.com/polygon-io/client-python
import time,tqdm
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
            # print(f"On: {resp.from_}\t{sym} opened at {resp.open} and closed at {resp.close}")
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
    # pyq.q("\l /home/acer/github/kdbLearn/companylist")
    T0 = time.time()
    pyq.q("symbols:(\"SSFSISS\";enlist\",\")0:`:/home/acer/github/kdbLearn/companylist.csv")


    pyq.q("quotes:(\"DSEEE\";enlist\",\")0:`:/home/acer/github/kdbLearn/quotes.csv")

    # pyq.q("`sym`date xkey `quotes")
    # pyq.q("`Symbol xkey `symbols")

    pyq.q("getallsymbols:{`Symbol xasc select Symbol from symbols}")
    quotes = pyq.q("showquotes:{`show quotes}")
    quotes.show()

    
    x = pyq.q.getallsymbols()
    # x.show()
    
    
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
    start = pd.to_datetime('December 1, 2019')
    end = pd.to_datetime('December 31, 2019')

    print("=============")
    # Get first day of every month:

    dateLst = pd.date_range(start, end).strftime('%Y.%m.%d').tolist()#, freq='MS'

    print("dateLst", dateLst)
    
    for name_idx in tqdm.tqdm(range(len(x))):
        name = x[name_idx]
        sym = str(name.Symbol)  
        print(sym, type(name.Symbol))
            # name.show()
        
        for date_str in dateLst:
            # print(sym, type(sym))
            resp = myClient.query(sym, date_str)
            if resp is not None:
                # `quotes upsert (`TURN;2017.12.01;2.04e;1.0709e;1.0709e)
                
                # print("type(resp.close )", type(resp.close))
                # query = f"`quotes upsert ([s:{date_str};`{sym}];{resp.open}e;{resp.close}e;{resp.close}e)"
                query = f"`quotes upsert ({date_str};`{sym};{resp.open}e;{resp.close}e;{resp.close}e)"
                # print(query)
                pyq.q(query)
    # pyq.q()
    # pyq.q("`symbol$() xkey `quotes")
    # pyq.q("`symbol$() xkey `symbols")
    # pyq.q("`:/home/acer/github/kdbLearn/companylist dsave `symbols`quotes")
    # pyq.q("`:/home/acer/github/kdbLearn/companylist dsave `symbols")
    # pyq.q("")
    # pyq.q("")
        pyq.q("`:/home/acer/github/kdbLearn/quotes.csv 0:.h.tx[`csv;quotes]")
        print("Elapsed time", time.time() - T0)