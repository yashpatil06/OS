a=1

while [ $a == 1 ]
do

echo -e "\nEnter Your Choice: "
echo -e "\n1.Create Address Book\n2.Insert Record\n3.Display Address Book\n4.Delete Record\n5.Modify a Record\n6.Exit"

read ch

case $ch in

1)
	echo -e "\nEnter Adress Book Name: "
	read fname
	touch $fname
	echo -e "\nFile Created Succesfully"
;;

2)
	echo -e "\nEnter the ID:"
	read id
	echo -e "\nEnter the Name:"
	read name
	echo -e "\nEnter the Roll No:"
	read roll
	
	echo -e "\n$id\t$name\t$roll" >> $fname
	
	echo -e "\nRecord Created Succesfully"
;;

3)
	if [ -s $fname ]
	then
	echo -e "\nID\tName\tRoll No"
	cat $fname
	else
	echo -e "\nFile is Empty"
	fi
;;

4)
	echo -e "\nEnter the Name of the Record to be deleted:"
	read dname
	
	sed -i '/'$dname'/d' $fname
	if [ $? == 0 ]
	then
	echo -e "\nRecord Deleted Succesfully"
	else
	echo -e "\nRecord Not Exist"
	fi
	
;;

5)
	echo -e "\nEnter the Name of the Record to be Modified:"
	read old
	
	grep $old $fname
	
	if [ $? == 0 ]
	then
	line=`grep -n $old $fname | cut -c 1`       #3   sid 37
	
	#output line=3
	echo -e "\nEnter The Modified Record Name:"
	read new
	sed -i "$line s/$old/$new/" $fname
	echo -e "\nModification Successful"
	else
	echo -e "\nSuch Record Does Not Exist"
	fi
;;

6)
	echo -e "\nExited Successfully"
;;

*)
	echo -e "\nInvalid Option"
;;
esac

echo -e "\nDo You Want To Continue(1/0)"
read a
done
