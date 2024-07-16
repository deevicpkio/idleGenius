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
OUTPUT=./build/raylib_app.out
if [[ -e $OUTPUT ]]
then
  rm $OUTPUT
fi

# NOTE: Execute compilation process
echo "-----------------------"
echo " Compiling Project ... "
echo "-----------------------"
echo " Output: $OUTPUT"
echo "-----------------------"

cmake -B build
cmake --build build/ -j4

# NOTE: Run application
if [[ -e $OUTPUT ]]
then
  echo "-------------------------"
  echo " COMPILATION SUCCESSFUL! "
  echo "-------------------------"
  
  if [[ $runAfter = true ]]
  then
    echo "-------------"
    echo " RUNNING ... "
    echo "-------------"
    ./run.sh
  fi
fi
