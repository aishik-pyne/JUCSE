if [ ! -f $1 ]; then
    echo "File not found!"
else
    wc -l $1
fi
