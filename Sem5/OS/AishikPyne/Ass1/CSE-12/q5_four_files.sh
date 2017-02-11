count=0
function occurence() {
    echo "In file $1"
    grep -c $2 $1
    count=$( grep -c $2 $1)
}


clear
if [ ! -f $1 -o ! -f $4 -o ! -f $3 -o ! -f $4 ]; then
    echo "Files not found!"
else
    sum=0
    occurence $1 $5
    ((sum+=count))
    occurence $2 $5
    ((sum+=count))
    occurence $3 $5
    ((sum+=count))
    occurence $4 $5
    ((sum+=count))
    echo "Grand Total Occurence $sum"
fi
