#!/bin/bash

if [ "$1x" == "x" ]; then
    echo "Please specify the exectuble file"
    exit 1
fi

EXE=$1
OUTPUT_FILE=$(mktemp)

$EXE $OUTPUT_FILE

if [ ! -f $OUTPUT_FILE ]; then
    echo "Index file was not created"
    exit 1
fi


EXP_MD5SUM="82da22bc7332c008c677ce1a9d09df35"
CUR_MD5SUM=$(md5sum $OUTPUT_FILE 2>/dev/null | awk '{print $1}')
if [ -z $CUR_MD5SUM ]; then
        printf "\x1b[31mFailed\x1b[0m\n"
else
    if [ $EXP_MD5SUM != $CUR_MD5SUM ]; then
        printf "\x1b[31mFailed\x1b[0m\n"
    else
        printf "\x1b[32mPassed\x1b[0m\n"
    fi
fi
