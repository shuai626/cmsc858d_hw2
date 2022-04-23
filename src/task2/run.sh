FILE=ecoli
QUERY=query
MODE=naive
OUT=out

for i in {1..6}
do
  ./querysa ../task1/${i} ../../test/31.fa naive ${i}_length | awk '{ sum += $2 } END { if (NR > 0) print sum / NR }'
done

for i in 21 31 41 51
do
  ./querysa ../task1/ecoli ../../test/${i}.fa naive naive_${i} | awk '{ sum += $2 } END { if (NR > 0) print sum / NR }'
done

for i in 21 31 41 51
do
  ./querysa ../task1/ecoli ../../test/${i}.fa simpaccel simpaccel_${i} | awk '{ sum += $2 } END { if (NR > 0) print sum / NR }'
done

for mode in naive simpaccel
do
  for in in ecoli _2 _4 _6 _8
  do
    ./querysa ../task1/${in} ../../test/31.fa $mode ${mode}_${in}  | awk '{ sum += $2 } END { if (NR > 0) print sum / NR }'
  done
done