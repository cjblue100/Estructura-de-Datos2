#!/bin/bash

if [ "$1x" == "x" ]; then
    echo "Please specify the executable file"
    exit 1
fi

APP=$1
JSON_DIR="./jfiles"
YAML_DIR="./yfiles"
JFILES="$JSON_DIR/ed2p42020.json $JSON_DIR/file1.json $JSON_DIR/menu.json $JSON_DIR/numbers.json"

for JFILE in $JFILES; do
    NAME=$(basename -s .json $JFILE)
    YFILE=$(mktemp)
    $APP $JFILE $YFILE
    if [ $? -ne 0 ]; then
        exit 1
    fi

    echo -n "Testing $JFILE ..."

    diff $YFILE $YAML_DIR/${NAME}.yml &> /dev/null
    if [ $? -ne 0 ]; then
        printf "%s \x1b[31mFailed\x1b[0m\n" $file
    else
        printf "%s \x1b[32mPassed\x1b[0m\n" $file
    fi
done