isPrime()
{
    i=2
    while [ $i -lt $1 ]
    do
        if [ `expr $1 % $i` -eq 0 ]
        then
          echo "$1 is not a prime number"
          echo "Since it is divisible by $i"
          exit
        fi
        i=`expr $i + 1`
    done
    echo "$num is prime"
}

isPrime $1
