for ((i=1;;++i)) do
./mkr > in
./$1 < in > out
./chk
done
