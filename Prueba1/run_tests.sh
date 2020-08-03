#~/bin/bash

TEST_DIR=tests
IMAGE_DIR=images

BMP_FILES=$(ls $IMAGE_DIR)
EXE=build/prueba1

mkdir -p $TEST_DIR/output

for file in $BMP_FILES; do
    NAME=$(basename -s .bmp $file)
    $EXE  $IMAGE_DIR/$file &> $TEST_DIR/output/${NAME}.txt
    diff $TEST_DIR/output/${NAME}.txt $TEST_DIR/expected/${NAME}.txt
    if [ $? -ne 0 ]; then
        printf "%s \x1b[31mFailed\x1b[0m\n" $file
    else
        printf "%s \x1b[32mPassed\x1b[0m\n" $file
    fi
done
