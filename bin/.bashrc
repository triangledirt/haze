RCFILES=`/bin/ls ~/.bashrc_* 2>/dev/null`
for FILE in $RCFILES; do
  #echo $FILE
  . $FILE
done
