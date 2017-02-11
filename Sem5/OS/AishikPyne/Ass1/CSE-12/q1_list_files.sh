for dir in $(find . -type d )
do
  echo $dir $(ls -A $dir | wc -l )
done
