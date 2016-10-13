#!/bin/bash
set -e

# Makes programs, downloads sample data, trains a GloVe model, and then evaluates it.
# One optional argument can specify the language used for eval script: matlab, octave or [default] python

mkdir demoBuild
cd demoBuild
cmake ..
make
cd demo
if [ ! -e text8 ]; then
  if hash wget 2>/dev/null; then
    wget http://mattmahoney.net/dc/text8.zip
  else
    curl -O http://mattmahoney.net/dc/text8.zip
  fi
  unzip text8.zip
  rm text8.zip
fi

CORPUS=text8

./glove_test_cpp

cd ../..

if [ "$CORPUS" = 'text8' ]; then
   if [ "$1" = 'matlab' ]; then
       echo "! matlab evaluation support has been removed in the glove_c fork because I don't want to maintain it."
   elif [ "$1" = 'octave' ]; then
       echo "! octave evaluation support has been removed in the glove_c fork because I don't want to maintain it."
   else
       echo "$ python eval/python/evaluate.py"
       python eval/python/evaluate.py --vocab_file demoBuild/demo/vocab.txt --vectors_file demoBuild/demo/vectors.txt
   fi
fi
