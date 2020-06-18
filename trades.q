/https://github.com/KxSystems/cookbook/blob/master/start/trades.q

/ trades.q
/ example table with random data

trades:([] date:`date$(); time:`time$(); sym:`symbol$(); price:`real$(); size:`int$(); cond:`char$())

＃yezheng's trade
trades:([] date:`date$();  sym:`symbol$(); price:`real$(); size:`int$())

`trades insert (2013.07.01;10:03:54.347;`IBM;20.83e;40000;"N")
`trades insert (2013.07.01;10:04:05.827;`MSFT;88.75e;2000;"B")
trades

syms:`IBM`MSFT`UPS`BAC`AAPL
tpd:1              / trades per day

cnt:count syms       / number of syms
day:5                / number of days
len:tpd*cnt*day      / total number of trades
len:2
date:2013.07.01+len?day
date: 2013.07.01 2013.07.03

time:"t"$raze (cnt*day)#enlist 09:30:00+15*til tpd
time+:len?1000
sym:len?syms
sym:`AAPL`MSFT
price:len?100e
price:33.53266 38.77171e
size:100*len?1000
size:78700 46000
cond:len?" ABCDENZ"

trades:0#trades      / empty trades table
`trades insert (date;time;sym;price;size;cond)
`trades insert (date;time;sym;price;size;cond)
`trades insert (2013.07.01 2013.07.03;`AAPL`MSFT;33.53266 38.77171e;78700 46000)
`date xkey `trades

`trades upsert (date;sym;price;size)
`trades insert (date;sym;price;size)
`trades insert (2013.07.01 2013.07.03;`AAPL`MSFT;33.53266 38.77171e;78700 46000)
`trades insert (2013.07.01 2013.07.03;`AAPL`MSFT;33.53266 38.77171e;78700 46000)

`trades upsert (2013.07.01 2013.07.03;`AAPL`MSFT;33.53266 38.77171e;78700 46000)
https://code.kx.com/q/ref/upsert/
## below works!!!
`trades upsert ([date:2013.07.01 2013.07.03]sym:`AAPL`MSFT;price:33.53266 38.77171e;size:78700 46000)
`trades upsert ([date:2013.07.01 2013.07.03]sym:`AAPL2`MSFT2;price:332.53266 382.77171e;size:787002 460002)
`trades upsert ([date:2013.07.01 2013.07.03]`AAPL`MSFT;33.53266 38.77171e;78700 46000)

trades:`date`time xasc trades  / sort on time within date
5#trades


`AAPLquotes upsert ([date:2020.05.01]volume:59350841e;high:299.0e;low:285.85e;adj_close:289.07e;close:289.07e;open:286.25e)

AAPLquotes upsert ([date:2020.05.01 2020.04.30]volume:59350841 37537233e;high:299.0 294.52e;low:285.85 288.36e;adj_close:289.07 293.8e;close:289.07 293.8e;open:286.25 289.96e)