#!/bin/bash
COUNTER_SUCCESS=0
COUNTER_FAIL=0
TEST_FILE1="test_file.txt"
TEST_FILE2="test_file2.txt"
TEST_FILE3="test_file3.txt"
TEST_FILE4="test_file_empty.txt"

if [[ "$OSTYPE" == "darwin"* ]]
then 
	flags_array=(-b -e -v -n -s -t)
	flags_array_no_dash=(b e v n s t)
elif [[ "$OSTYPE" == "linux-gnu"* ]]
then 
	flags_array=(-b -e -v -n -s -t -E -T --number-nonblank --number --squeeze-blank)
fi

echo "Testing processing. Wait..."

#test code with one flag
for var in ${flags_array[@]}
do
	TEST1="$var $TEST_FILE1"
	./s21_cat $TEST1 > s21_cat.txt
	cat $TEST1 > cat.txt
	DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
	if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
		then
			((COUNTER_SUCCESS++))
		else
			echo "Test case $var failed"
			((COUNTER_FAIL++))
	fi
done

#test code with two flags separate
for var1 in ${flags_array[@]}
do
	for var2 in ${flags_array[@]}
	do
		if [ $var1 != $var2 ]
		then
			TEST2="$var1 $var2 $TEST_FILE1"
			./s21_cat $TEST2 > s21_cat.txt
			cat $TEST2 > cat.txt
			DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
			if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
				then
					((COUNTER_SUCCESS++))
				else
					echo "Test case $var1 $var2 failed"
					((COUNTER_FAIL++))
			fi
		fi
	done
done

#flags list to long for linux. 3,4,5 flag combinations only for darwin + flags without dash
if [[ "$OSTYPE" == "darwin"* ]]
then 
	#test code with three flags separate
	for var1 in ${flags_array[@]}
	do
		for var2 in ${flags_array[@]}
		do
			for var3 in ${flags_array[@]}
			do
				if [ $var1 != $var2 ] && [ $var1 != $var3 ] && [ $var2 != $var3 ]
				then
					TEST3="$var1 $var2 $var3 $TEST_FILE1"
					./s21_cat $TEST3 > s21_cat.txt
					cat $TEST3 > cat.txt
					DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
					if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
						then
							((COUNTER_SUCCESS++))
						else
							echo "Test case $var1 $var2 $var3 failed"
							((COUNTER_FAIL++))
					fi
				fi
			done
		done
	done

	#test code with four flags separate
	for var1 in ${flags_array[@]}
	do
		for var2 in ${flags_array[@]}
		do
			for var3 in ${flags_array[@]}
			do
				for var4 in ${flags_array[@]}
				do
					if [ $var1 != $var2 ] && [ $var1 != $var3 ] && [ $var1 != $var4 ] && [ $var2 != $var3 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
					then
						TEST4="$var1 $var2 $var3 $var4 $TEST_FILE1"
						./s21_cat $TEST4 > s21_cat.txt
						cat $TEST4 > cat.txt
						DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
						if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
							then
								((COUNTER_SUCCESS++))
							else
								echo "Test case $var1 $var2 $var3 $var4 failed"
								((COUNTER_FAIL++))
						fi
					fi
				done
			done
		done
	done

	#test code with five flags separate
	for var1 in ${flags_array[@]}
	do
		for var2 in ${flags_array[@]}
		do
			for var3 in ${flags_array[@]}
			do
				for var4 in ${flags_array[@]}
				do
					for var5 in ${flags_array[@]}
					do
						if [ $var1 != $var2 ] && [ $var1 != $var3 ] && [ $var1 != $var4 ] && [ $var1 != $var5 ] && [ $var2 != $var3 ] && [ $var2 != $var4 ] && [ $var2 != $var5 ] && [ $var3 != $var4 ] && [ $var3 != $var5 ]&& [ $var4 != $var5 ]
						then
							TEST5="$var1 $var2 $var3 $var4 $var5 $TEST_FILE1"
							./s21_cat $TEST5 > s21_cat.txt
							cat $TEST5 > cat.txt
							DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
							if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
								then
									((COUNTER_SUCCESS++))
								else
									echo "Test case $var1 $var2 $var3 $var4 $var5 failed"
									((COUNTER_FAIL++))
							fi
						fi
					done
				done
			done
		done
	done
	
	#test code with two flags PAIR (one pair works - all combination works)
	for var1 in ${flags_array_no_dash[@]}
	do
		for var2 in ${flags_array_no_dash[@]}
		do
			if [ $var1 != $var2 ]
			then
				TEST8="-$var1$var2 $TEST_FILE1"
				./s21_cat $TEST8 > s21_cat.txt
				cat $TEST8 > cat.txt
				DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
				if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
					then
						((COUNTER_SUCCESS++))
					else
						echo "Test case -$var1$var2 failed"
						((COUNTER_FAIL++))
				fi
			fi
		done
	done
fi

#test code with six flags separate (different order)
TEST7=" -t -s -n -v -e -b $TEST_FILE1"
./s21_cat $TEST7 > s21_cat.txt
cat $TEST7 > cat.txt
DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "Test case -t -s -n -v -e -b failed"
		((COUNTER_FAIL++))
fi

#test code with several single flags
TEST9="-bbbbbbb $TEST_FILE1"
./s21_cat $TEST9 > s21_cat.txt
cat $TEST9 > cat.txt
DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "Test case -bbbbbbb failed"
		((COUNTER_FAIL++))
fi

#test code with no flags
TEST10="$TEST_FILE1"
./s21_cat $TEST10 > s21_cat.txt
cat $TEST10 > cat.txt
DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "Test case (noflgs) failed"
		((COUNTER_FAIL++))
fi

#test code several text files
TEST14="$TEST_FILE1 $TEST_FILE2 $TEST_FILE3"
./s21_cat $TEST14 > s21_cat.txt
cat $TEST14 > cat.txt
DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "Test case several text files failed"
		((COUNTER_FAIL++))
fi

#test code several text files -n
for var in -n -b -s
do
	TEST15="-n $TEST_FILE2 $TEST_FILE3"
	./s21_cat $TEST15 > s21_cat.txt
	cat $TEST15 > cat.txt
	DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
	if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
		then
			((COUNTER_SUCCESS++))
		else
			echo "Test case several files $var failed"
			((COUNTER_FAIL++))
	fi
done

rm s21_cat.txt cat.txt
echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
