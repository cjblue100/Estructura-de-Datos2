#!/bin/bash

TEST_DIR=test
IMAGE_DIR=images

BMP_FILES="Marbles_8bpp.bmp penguins_8bpp.bmp"
MD5_SUMS=("e2550b218c627d5a4a351f994d5af7b1" "f84e8606a5fce71dc1bb18242300250e")
EXE="build/prueba2"

mkdir -p $TEST_DIR

INDEX=0
for file in $BMP_FILES; do
    NAME=$(basename -s .bmp $file)
    $EXE  $IMAGE_DIR/$file $TEST_DIR/${NAME}_new.bmp
    if [ $? -ne 0 ]; then
        exit 1
    fi
    
    MD5_SUM=$(md5sum $TEST_DIR/${NAME}_new.bmp | awk '{print $1}')
    if [ $? -ne 0 ]; then
        exit 1
    fi
    
    EXP_MD5SUM=${MD5_SUMS[$INDEX]}
    
    if [ $EXP_MD5SUM != $MD5_SUM ]; then
        printf "%s \x1b[31mFailed\x1b[0m\n" $file
    else
        printf "%s \x1b[32mPassed\x1b[0m\n" $file
    fi
    INDEX=$(( INDEX + 1 ))
done
