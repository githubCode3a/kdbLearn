https://stackoverflow.com/questions/25338608/download-all-stock-symbol-list-of-a-market
http://www.nasdaq.com/screening/companies-by-industry.aspx?exchange=NASDAQ&render=download
All symbols (companylist.csv)


API j1oP5-4ifJTP5XzEpRAv
https://www.quandl.com/?utm_source=google&utm_medium=organic&utm_campaign=&utm_content=api-for-stock-data
https://blog.quandl.com/api-for-stock-data

https://www.quandl.com/api/v3/datasets/EOD/AAPL.csv?api_key=j1oP5-4ifJTP5XzEpRAv

https://www.quandl.com/api/v3/datatables/SHARADAR/SF1.csv?ticker=AAPL&qopts.columns=ticker,dimension,datekey,revenue&api_key=j1oP5-4ifJTP5XzEpRAv


https://polygon.io/

aGls_e4_gw0XgXU_XY64XFrrP88o_tcQ3qmYWY



Rapid  API


\l /home/acer/github/kdbLearn/companylist

symbols:("SS";enlist",")0:`:/home/acer/github/kdbLearn/companylist.csv
getallsymbols:{select from symbols}
f:{select from symbols}


`:/home/acer/github/kdbLearn/companylist dsave `symbols

`:/home/acer/github/kdbLearn/companylist dsave `symbols`quotes


##yezheng: but not importing everything
x = q.getallsymbols()
x = q.f()


`:/home/acer/github/kdbLearn/db1 dsave`sym xasc'`t`q --> create FOLDER db1


#---------
<!-- https://code.kx.com/q/learn/startingkdb/tables/ -->
create an empty table
quotes:([]sym:`symbol$();date:`date$();spot:`real$();open:`real$();close:`real$())
`:/home/acer/github/kdbLearn/quotes dsave `quotes
`:/home/acer/github/kdbLearn/quotes dsave `quotes

`quotes upsert (`TURN;2017.12.01;2.04e;1.0709e;1.0709e)

TURN opened at 2.04 and closed at 1.9709



trades:([]date:`date$();time:`time$();sym:`symbol$(); price:`real$();size:`int$(); cond:`char$())


`trades insert (2013.07.01;10:03:54.347;`IBM;20.83e;40000;"N")


trades:([]date:`date$();sym:`symbol$(); price:`real$();size:`int$())


`trades insert (2013.07.01;`IBM;20.83e;40000)


`:/home/acer/github/kdbLearn/trades dsave `trades