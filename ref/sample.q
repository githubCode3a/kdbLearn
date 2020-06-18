/https://code.kx.com/q/learn/brief-introduction/

n:1000000
item:`apple`banana`orange`pear
city:`beijing`chicago`london`paris
tab:([]time:asc n?0D0;n?item;amount:n?100;n?city)

select sum amount by city from tab

select sum amount by time.hh,item from tab 


\t select from tab
