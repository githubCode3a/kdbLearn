# https://github.com/polygon-io/client-python
import time
import pandas as pd
import pyq
from datetime import date
import q 
from polygon import WebSocketClient, STOCKS_CLUSTER


def my_customer_process_message(message):
    print("this is my custom message processing", message)


def main():
    key = 'aGls_e4_gw0XgXU_XY64XFrrP88o_tcQ3qmYWY'
    my_client = WebSocketClient(STOCKS_CLUSTER, key, my_customer_process_message)
    my_client.run_async()

    my_client.subscribe("T.MSFT", "T.AAPL", "T.AMD", "T.NVDA")
    time.sleep(2)

    my_client.close_connection()


if __name__ == "__main__":
    df = pd.read_csv("~/github/kdbLearn/companylist.csv")
    
    c=q.conn(host="127.0.0.1",port=12345)
    print(c('1+1'))

    # x = pyq.getallsymbols()