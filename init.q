\cd /home/acer/github/kdbLearn/
symbols:("SS";enlist",")0:`:/home/acer/github/kdbLearn/companylist.csv


quotes:([]date:`date$();sym:`symbol$();spot:`real$();open:`real$();close:`real$())

`:/home/acer/github/kdbLearn/companylist dsave `symbols`quotes
