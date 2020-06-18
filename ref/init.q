\cd /home/acer/github/kdbLearn/
symbols: ("SSFSISS";enlist csv) 0: `:/home/acer/github/kdbLearn/companylist.csv


quotes:("DSEEE";enlist",")0:`:/home/acer/github/kdbLearn/quotes.csv
//quotes:([]date:`date$();sym:`symbol$();spot:`real$();open:`real$();close:`real$())

trades:([]date:`date$();time:`time$();sym:`symbol$(); price:`real$();size:`int$(); cond:`char$())

`:/home/acer/github/kdbLearn/quotes.csv 0:.h.tx[`csv;quotes]