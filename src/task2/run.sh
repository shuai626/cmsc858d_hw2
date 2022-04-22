FILE=ecoli
QUERY=query
MODE=naive
OUT=out

for i in {1..6}
do
  for j in 21 31 41 51
  do
    echo ${i}_${j}
    ./querysa ../task1/${i} ../../test/${j}.fa naive ${i}_${j} > naive_${i}_${j}.timing
  done
done

for i in {1..6}
do
  for j in 21 31 41 51
  do
    echo ${i}_${j}
    ./querysa ../task1/${i} ../../test/${j}.fa simpaccel ${i}_${j} > simpaccel_${i}_${j}.timing
  done
done

for mode in naive simpaccel
do
  for in in ecoli _2 _4 _6 _8
  do
    ./querysa ../task1/${in} ../../test/query.fa $mode ${mode}_${in} > ${mode}_${in}.timing
  done
done