#!/bin/bash

if [ "$1x" == "x" ]; then
    echo "Please specify the exectuble file"
    exit 1
fi

EXE=$1
INPUT_FILES="files/random_data.bin files/random_data.txt files/thousand_numbers.txt"
OUTPUT_FILE=$(mktemp)

$EXE $INPUT_FILES $OUTPUT_FILE

# Test 1
echo -n "Checking if the file is a zip archive ... "
file $OUTPUT_FILE | grep -i "zip archive" &> /dev/null
if [ $? -ne 0 ]; then
    printf "\x1b[31mFailed\x1b[0m\n"
else
    printf "\x1b[32mPassed\x1b[0m\n"
fi

# Test 2
echo -n "Checking if 'unzip' recognize the file ... "
unzip -l $OUTPUT_FILE &> /dev/null
if [ $? -ne 0 ]; then
    printf "\x1b[31mFailed\x1b[0m\n"
else
    printf "\x1b[32mPassed\x1b[0m\n"
fi

# Test 3
SIZES="4096 5536 13000"
for size in $SIZES; do
    echo -n "Checking file size $size ... "
    unzip -l $OUTPUT_FILE 2>/dev/null | grep $size &>/dev/null
    if [ $? -ne 0 ]; then
        printf "\x1b[31mFailed\x1b[0m\n"
    else
        printf "\x1b[32mPassed\x1b[0m\n"
    fi
done

# Test 4
for file in $INPUT_FILES; do
    echo -n "Checking file name $file ... "
    NAME=$(unzip -l $OUTPUT_FILE 2>/dev/null | grep $file | awk '{print $4}')
    if [ "$NAME" != "$file" ]; then
        printf "\x1b[31mFailed\x1b[0m\n"
    else
        printf "\x1b[32mPassed\x1b[0m\n"
    fi
done

# Test 5
MD5SUMS=("5c1ba6725bc76e3ae5374b5ef83dd55e" "cc66512b50357ff3207e70e04803a71c" "dd463a43db4d75f42a3a70a58c5e967a")
INDEX=0

rm -fr tmp/
mkdir -p tmp/
unzip -d tmp/ $OUTPUT_FILE &> /dev/null

for file in $INPUT_FILES; do
    echo -n "Checking file content $file ... "
    EXP_MD5SUM=${MD5SUMS[INDEX]}
    CUR_MD5SUM=$(md5sum ./tmp/$file 2>/dev/null | awk '{print $1}')
    if [ "${CUR_MD5SUM}x" == "x" ]; then
        printf "\x1b[31mFailed\x1b[0m\n"
    else
        if [ $EXP_MD5SUM != $CUR_MD5SUM ]; then
            printf "\x1b[31mFailed\x1b[0m\n"
        else
            printf "\x1b[32mPassed\x1b[0m\n"
        fi
    fi
    INDEX=$(( INDEX + 1 ))
done

# Test 6
EXP_MD5SUM="e294e80860d4d74c138cc791bcdb863c"
CUR_MD5SUM=$(md5sum $OUTPUT_FILE | awk '{print $1}')
echo -n "Checking the ZIP file ... "
if [ $EXP_MD5SUM != $CUR_MD5SUM ]; then
    printf "\x1b[31mFailed\x1b[0m\n"
else
    printf "\x1b[32mPassed\x1b[0m\n"
fi
