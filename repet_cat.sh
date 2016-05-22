
for cnt in `seq -w 1 $1`
do
	if [ $cnt -ne 1 ];
	then
		echo -n ",RESET,"
	fi

	cat $2
done
