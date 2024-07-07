#!/usr/bin/bash


clear

# NOTE: Handle parameters
verboseMode=""
runAfter=false

for var in "$@"
do
    if [[ $var = "-v" ]]
    then
        verboseMode=$var
    fi

    if [[ $var = "-r" ]]
    then
        runAfter=true
    fi
done

# NOTE: Prepare output (delete previous version on destination)
OUTPUT=./build/bin/app.out
if [[ -e $OUTPUT ]]
then
  rm $OUTPUT
fi

# NOTE: Prepare source code list to compile
FILE_LIST='./src'
for entry in "$FILE_LIST"/*.cpp
do
  SOURCES="$SOURCES $entry"
done
for entry in "$FILE_LIST"/*/*.cpp
do
  SOURCES="$SOURCES $entry"
done

# NOTE: Prepare vendor headers 
DIR_LIST='./vendor'
for entry in "$DIR_LIST"/*/
do
  VENDOR="$VENDOR $entry"
done

# NOTE: Execute compilation process
echo "-----------------------"
echo " Compiling Project ... "
echo "-----------------------"
echo " Output: $OUTPUT"
echo " SOURCES: $SOURCES"
echo " INCLUDING> $VENDOR"
echo "-----------------------"

clang++ $SOURCES -o $OUTPUT -std=c++20 -I $VENDOR -lraylib -lGL -lsqlite3 -lspdlog -lfmt -lm -lpthread -ldl -lrt -lX11 $verboseMode

# NOTE: Run application
if [[ -e $OUTPUT ]]
then
  echo "---------------------------"
  echo "  COMPILATION SUCCESSFUL! "
  echo "---------------------------"
  
  if [[ $runAfter = true ]]
  then
    echo "-------------"
    echo " RUNNING ... "
    echo "-------------"
    ./run.sh
  fi
fi
