#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
PATTERN_WORD_1="HI"
PATTERN_WORD_2="BASH"
PATTERN_WORD_3="hi"
PATTERN_WORD_4="tadadam"
TEST_FILE1="test_file1.txt"
TEST_FILE2="test_file2.txt"
PATTERN_FILE="test_file3.txt"
TEST_FILE4="test_file_empty.txt"
TEST_FILE5="test_file_not_exist.txt"

flags_array=(-i -v -c -l -n -h) 


echo "Testing processing. Wait..."

#code block with -e flag
#-------------------------------------

#test case: 1 pattern 1 file
TEST_NAME="TEST1 e flag"
TEST1="$PATTERN_WORD_1 $TEST_FILE1"
./s21_grep $TEST1 > s21_grep.txt 2>&1
grep $TEST1 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST1"
		((COUNTER_FAIL++))
fi

#test case: -e 1 pattern 1 file
TEST_NAME="TEST2 e flag"
TEST2="-e $PATTERN_WORD_1 $TEST_FILE1"
./s21_grep $TEST2 > s21_grep.txt 2>&1
grep $TEST2 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST2"
		((COUNTER_FAIL++))
fi

#test case: -e 1 pattern 1 file indirect order
TEST_NAME="TEST3 e flag"
TEST3="$TEST_FILE1 -e $PATTERN_WORD_1"
./s21_grep $TEST3 > s21_grep.txt 2>&1
grep $TEST3 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST3"
		((COUNTER_FAIL++))
fi

#test case: -e 2 pattern 1 file
TEST_NAME="TEST4 e flag"
TEST4="-e $PATTERN_WORD_1 -e $PATTERN_WORD_2 $TEST_FILE1"
./s21_grep $TEST4 > s21_grep.txt 2>&1
grep $TEST4 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST4"
		((COUNTER_FAIL++))
fi

#test case: -e 1 pattern + pattern 1 file
TEST_NAME="TEST5 e flag"
TEST5="$PATTERN_WORD_1 -e $PATTERN_WORD_2 $TEST_FILE1"
./s21_grep $TEST5 > s21_grep.txt 2>&1
grep $TEST5 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST5"
		((COUNTER_FAIL++))
fi

#test case: -e 1 pattern 2 file
TEST_NAME="TEST6 e flag"
TEST6="-e $PATTERN_WORD_1 $TEST_FILE1 $TEST_FILE2"
./s21_grep $TEST6 > s21_grep.txt 2>&1
grep $TEST6 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST6"
		((COUNTER_FAIL++))
fi

#test case: -e 2 pattern 2 file
TEST_NAME="TEST7 e flag"
TEST7="-e $PATTERN_WORD_1 -e $PATTERN_WORD_2 $TEST_FILE1 $TEST_FILE2"
./s21_grep $TEST7 > s21_grep.txt 2>&1
grep $TEST7 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST7"
		((COUNTER_FAIL++))
fi

#test case: -e several patterns 2 file
TEST_NAME="TEST8 e flag"
TEST8="-e $PATTERN_WORD_1 -e $PATTERN_WORD_2 -e $PATTERN_WORD_3 -e $PATTERN_WORD_4 $TEST_FILE1 $TEST_FILE2"
./s21_grep $TEST8 > s21_grep.txt 2>&1
grep $TEST8 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST8"
		((COUNTER_FAIL++))
fi

#test case: empty file
TEST_NAME="TEST9 e flag"
TEST9="-e $PATTERN_WORD_1 $TEST_FILE4"
./s21_grep $TEST9 > s21_grep.txt 2>&1
grep $TEST9 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST9"
		((COUNTER_FAIL++))
fi

#test case: file is not exist
TEST_NAME="TEST10 e flag"
TEST10="-e $PATTERN_WORD_1 $TEST_FILE5"
./s21_grep $TEST10 > s21_grep.txt 2>&1
grep $TEST10 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST10"
		((COUNTER_FAIL++))
fi

#test case: no pattern word in file
TEST_NAME="TEST12 e flag"
TEST12="-e $PATTERN_WORD_4 $TEST_FILE1"
./s21_grep $TEST12 > s21_grep.txt 2>&1
grep $TEST12 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST12"
		((COUNTER_FAIL++))
fi

#code block with flags array
#-------------------------------------

#test case: 1 pattern + flag + 1 file 
for var in ${flags_array[@]}
do
	TEST_NAME="TEST13 $var flag"
	TEST13="-e $PATTERN_WORD_3 $var $TEST_FILE1"
	./s21_grep $TEST13 > s21_grep.txt 2>&1
	grep $TEST13 > grep.txt 2>&1
	DIFF_RES="$(diff s21_grep.txt grep.txt)"
	if [ "$DIFF_RES" == "" ]
		then
			((COUNTER_SUCCESS++))
		else
			echo "$TEST_NAME failed: $TEST13"
			((COUNTER_FAIL++))
	fi
done

#test case: flag + 1 pattern + 1 file 
for var in ${flags_array[@]}
do
	TEST_NAME="TEST14 $var flag"
	TEST14="$var -e $PATTERN_WORD_1 $TEST_FILE1"
	./s21_grep $TEST14 > s21_grep.txt 2>&1
	grep $TEST14 > grep.txt 2>&1
	DIFF_RES="$(diff s21_grep.txt grep.txt)"
	if [ "$DIFF_RES" == "" ]
		then
			((COUNTER_SUCCESS++))
		else
			echo "$TEST_NAME failed: $TEST14"
			((COUNTER_FAIL++))
	fi
done

#test case: flag + 1 pattern + 1 file 
for var in ${flags_array[@]}
do
	TEST_NAME="TEST14 $var flag"
	TEST14="$var -e $PATTERN_WORD_3 $TEST_FILE1"
	./s21_grep $TEST14 > s21_grep.txt 2>&1
	grep $TEST14 > grep.txt 2>&1
	DIFF_RES="$(diff s21_grep.txt grep.txt)"
	if [ "$DIFF_RES" == "" ]
		then
			((COUNTER_SUCCESS++))
		else
			echo "$TEST_NAME failed: $TEST14"
			((COUNTER_FAIL++))
	fi
done

#test case: 1 pattern + 1 file + flag
for var in ${flags_array[@]}
do
	TEST_NAME="TEST14 $var flag"
	TEST14="-e $PATTERN_WORD_3 $TEST_FILE1 $var"
	./s21_grep $TEST14 > s21_grep.txt 2>&1
	grep $TEST14 > grep.txt 2>&1
	DIFF_RES="$(diff s21_grep.txt grep.txt)"
	if [ "$DIFF_RES" == "" ]
		then
			((COUNTER_SUCCESS++))
		else
			echo "$TEST_NAME failed: $TEST14"
			((COUNTER_FAIL++))
	fi
done

#test case: 2 patterns + flag + 2 files 
for var in ${flags_array[@]}
do
	TEST_NAME="TEST15 $var flag"
	TEST15="-e $PATTERN_WORD_1 -e $PATTERN_WORD_3 $var $TEST_FILE1 $TEST_FILE2"
	./s21_grep $TEST15 > s21_grep.txt 2>&1
	grep $TEST15 > grep.txt 2>&1
	DIFF_RES="$(diff s21_grep.txt grep.txt)"
	if [ "$DIFF_RES" == "" ]
		then
			((COUNTER_SUCCESS++))
		else
			echo "$TEST_NAME failed: $TEST15"
			((COUNTER_FAIL++))
	fi
done

#test case: 3 patterns + flag + 2 files 
for var in ${flags_array[@]}
do
	TEST_NAME="TEST15 $var flag"
	TEST15="-e $PATTERN_WORD_1 -e $PATTERN_WORD_2 -e $PATTERN_WORD_3 $var $TEST_FILE1 $TEST_FILE2"
	./s21_grep $TEST15 > s21_grep.txt 2>&1
	grep $TEST15 > grep.txt 2>&1
	DIFF_RES="$(diff s21_grep.txt grep.txt)"
	if [ "$DIFF_RES" == "" ]
		then
			((COUNTER_SUCCESS++))
		else
			echo "$TEST_NAME failed: $TEST15"
			((COUNTER_FAIL++))
	fi
done

#test case: 2 patterns + flag + file_is_not_exist
for var in ${flags_array[@]}
do
	TEST_NAME="TEST16 $var flag"
	TEST16="-e $PATTERN_WORD_1 -e $PATTERN_WORD_3 $var $TEST_FILE5"
	./s21_grep $TEST16 > s21_grep.txt 2>&1
	grep $TEST16 > grep.txt 2>&1
	DIFF_RES="$(diff s21_grep.txt grep.txt)"
	if [ "$DIFF_RES" == "" ]
		then
			((COUNTER_SUCCESS++))
		else
			echo "$TEST_NAME failed: $TEST16"
			((COUNTER_FAIL++))
	fi
done

#test case: 2 patterns + flag + file_is_empty
for var in ${flags_array[@]}
do
	TEST_NAME="TEST16 $var flag"
	TEST16="-e $PATTERN_WORD_1 -e $PATTERN_WORD_3 $var $TEST_FILE4"
	./s21_grep $TEST16 > s21_grep.txt 2>&1
	grep $TEST16 > grep.txt 2>&1
	DIFF_RES="$(diff s21_grep.txt grep.txt)"
	if [ "$DIFF_RES" == "" ]
		then
			((COUNTER_SUCCESS++))
		else
			echo "$TEST_NAME failed: $TEST16"
			((COUNTER_FAIL++))
	fi
done

#code block with -f flag
#-------------------------------------

#test case: 1 f_pattern(2pat) 1 file
TEST_NAME="TEST1 f flag"
TEST1="-f $PATTERN_FILE $TEST_FILE1"
./s21_grep $TEST1 > s21_grep.txt 2>&1
grep $TEST1 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST1"
		((COUNTER_FAIL++))
fi

#test case: 1 pattern 1 e_pattern 1 f_pattern(2pat) 1 file
TEST_NAME="TEST1 f flag"
TEST1="$PATTERN_WORD_1 -e $PATTERN_WORD_2 -f $PATTERN_FILE $TEST_FILE1"
./s21_grep $TEST1 > s21_grep.txt 2>&1
grep $TEST1 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST1"
		((COUNTER_FAIL++))
fi

#test case: empty f_pattern(2pat) 1 file
TEST_NAME="TEST1 f flag"
TEST1="-f $TEST_FILE4 $TEST_FILE1"
./s21_grep $TEST1 > s21_grep.txt 2>&1
grep $TEST1 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST1"
		((COUNTER_FAIL++))
fi

#code block with -s flag
#-------------------------------------

#test case: file is not exist
TEST_NAME="TEST1 f flag"
TEST1="-e $PATTERN_WORD_1 -s $TEST_FILE5"
./s21_grep $TEST1 > s21_grep.txt 2>&1
grep $TEST1 > grep.txt 2>&1
DIFF_RES="$(diff s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "" ]
	then
		((COUNTER_SUCCESS++))
	else
		echo "$TEST_NAME failed: $TEST1"
		((COUNTER_FAIL++))
fi



#code block with double flags
#-------------------------------------
flags_array=(-i -v -c -l -n -h)
for var1 in ${flags_array[@]}
  	do
      	for var2 in ${flags_array[@]}
      	do
        	if [ $var != $var2 ]
        	then
        	#test case: 1 pattern + flag + 1 file 
			TEST_NAME="TEST13 $var1 $var2 flag"
			TEST13="-e $PATTERN_WORD_3 $var1 $var2 $TEST_FILE1"
			./s21_grep $TEST13 > s21_grep.txt 2>&1
			grep $TEST13 > grep.txt 2>&1
			DIFF_RES="$(diff s21_grep.txt grep.txt)"
			if [ "$DIFF_RES" == "" ]
				then
					((COUNTER_SUCCESS++))
				else
					echo "$TEST_NAME failed: $TEST13"
					((COUNTER_FAIL++))
			fi

			#test case: flag + 1 pattern + 1 file 
			TEST_NAME="TEST14 $var1 $var2 flag"
			TEST14="$var1 $var2 -e $PATTERN_WORD_1 $TEST_FILE1"
			./s21_grep $TEST14 > s21_grep.txt 2>&1
			grep $TEST14 > grep.txt 2>&1
			DIFF_RES="$(diff s21_grep.txt grep.txt)"
			if [ "$DIFF_RES" == "" ]
				then
					((COUNTER_SUCCESS++))
				else
					echo "$TEST_NAME failed: $TEST14"
					((COUNTER_FAIL++))
			fi

			#test case: flag + 1 pattern + 1 file 
			TEST_NAME="TEST14 $var1 $var2 flag"
			TEST14="$var1 $var2 -e $PATTERN_WORD_3 $TEST_FILE1"
			./s21_grep $TEST14 > s21_grep.txt 2>&1
			grep $TEST14 > grep.txt 2>&1
			DIFF_RES="$(diff s21_grep.txt grep.txt)"
			if [ "$DIFF_RES" == "" ]
				then
					((COUNTER_SUCCESS++))
				else
					echo "$TEST_NAME failed: $TEST14"
					((COUNTER_FAIL++))
			fi

			#test case: 1 pattern + 1 file + flag
			TEST_NAME="TEST14 $var1 $var2 flag"
			TEST14="-e $PATTERN_WORD_3 $TEST_FILE1 $var1 $var2"
			./s21_grep $TEST14 > s21_grep.txt 2>&1
			grep $TEST14 > grep.txt 2>&1
			DIFF_RES="$(diff s21_grep.txt grep.txt)"
			if [ "$DIFF_RES" == "" ]
				then
					((COUNTER_SUCCESS++))
				else
					echo "$TEST_NAME failed: $TEST14"
					((COUNTER_FAIL++))
			fi

			#test case: 2 patterns + flag + 2 files 
			TEST_NAME="TEST15 $var flag"
			TEST15="-e $PATTERN_WORD_1 -e $PATTERN_WORD_3 $var $TEST_FILE1 $TEST_FILE2"
			./s21_grep $TEST15 > s21_grep.txt 2>&1
			grep $TEST15 > grep.txt 2>&1
			DIFF_RES="$(diff s21_grep.txt grep.txt)"
			if [ "$DIFF_RES" == "" ]
				then
					((COUNTER_SUCCESS++))
				else
					echo "$TEST_NAME failed: $TEST15"
					((COUNTER_FAIL++))
			fi

			#test case: 3 patterns + flag + 2 files 
			TEST_NAME="TEST15 $var flag"
			TEST15="-e $PATTERN_WORD_1 -e $PATTERN_WORD_2 -e $PATTERN_WORD_3 $var $TEST_FILE1 $TEST_FILE2"
			./s21_grep $TEST15 > s21_grep.txt 2>&1
			grep $TEST15 > grep.txt 2>&1
			DIFF_RES="$(diff s21_grep.txt grep.txt)"
			if [ "$DIFF_RES" == "" ]
				then
					((COUNTER_SUCCESS++))
				else
					echo "$TEST_NAME failed: $TEST15"
					((COUNTER_FAIL++))
			fi

			#test case: 2 patterns + flag + file_is_not_exist
			TEST_NAME="TEST16 $var flag"
			TEST16="-e $PATTERN_WORD_1 -e $PATTERN_WORD_3 $var $TEST_FILE5"
			./s21_grep $TEST16 > s21_grep.txt 2>&1
			grep $TEST16 > grep.txt 2>&1
			DIFF_RES="$(diff s21_grep.txt grep.txt)"
			if [ "$DIFF_RES" == "" ]
				then
					((COUNTER_SUCCESS++))
				else
					echo "$TEST_NAME failed: $TEST16"
					((COUNTER_FAIL++))
			fi

			#test case: 2 patterns + flag + file_is_empty
			TEST_NAME="TEST16 $var flag"
			TEST16="-e $PATTERN_WORD_1 -e $PATTERN_WORD_3 $var $TEST_FILE4"
			./s21_grep $TEST16 > s21_grep.txt 2>&1
			grep $TEST16 > grep.txt 2>&1
			DIFF_RES="$(diff s21_grep.txt grep.txt)"
			if [ "$DIFF_RES" == "" ]
				then
					((COUNTER_SUCCESS++))
				else
					echo "$TEST_NAME failed: $TEST16"
					((COUNTER_FAIL++))
			fi
			fi

    	done
	done

rm s21_grep.txt grep.txt
echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
