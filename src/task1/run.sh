FILE=ecoli

./buildsa ../../test/1.fa 1
./buildsa ../../test/2.fa 2
./buildsa ../../test/3.fa 3
./buildsa ../../test/4.fa 4
./buildsa ../../test/5.fa 5
./buildsa ../../test/6.fa 6

./buildsa ../../test/$FILE.fa $FILE

./buildsa --preftab 2 ../../test/$FILE.fa _2
./buildsa --preftab 4 ../../test/$FILE.fa _4
./buildsa --preftab 6 ../../test/$FILE.fa _6
./buildsa --preftab 8 ../../test/$FILE.fa _8