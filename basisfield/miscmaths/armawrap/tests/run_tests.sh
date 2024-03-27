#!/bin/bash

# if any arguments are specified, they will override
# environment CXXFLAGS - see the Makefile
if [ "$#" -ne 0 ]; then
  export CXXFLAGS="$@"
fi

if [ -z "$GCOV" ]; then
  export GCOV=gcov
fi

alias lcov="lcov --gcov-tool=$GCOV"

if [ -z "$ARMAWRAP_INCLUDE_DIR" ]; then
  export ARMAWRAP_INCLUDE_DIR=$(cd $(dirname $0) && pwd)/../
fi

function dotest() {

  lib=$1
  cov=$2
  status=0

  if ! command -v lcov > /dev/null; then
    cov=""
  fi

  echo "Compiling tests against $lib..."
  make clean
  if ! make LIB=$lib; then
    echo "$lib compilation failed!"
    return 1
  fi


  if [ "$cov" != "" ]; then
    lcov -c -i -b . -d . -o cov.baseline > /dev/null

  fi

  echo "Running tests against $lib..."
  for srcfile in *.cpp; do
    execfile=`basename $srcfile .cpp`

    if [ ! -f $execfile ]; then
      continue
    fi

    outfile="$lib"_"$execfile".txt
    benchmark=benchmarks/$outfile

    if ! ./$execfile > $outfile; then
      echo "$execfile[$lib] errored!"
      status=1
      continue
    fi

    if ! cmp -s $outfile $benchmark; then
      echo "$execfile[$lib] failed!"
      status=1
      continue
    fi

    rm $outfile
  done

  if [ "$cov" != "" ]; then
    echo "Generating coverage report..."
    lcov -c -d . -b . -o cov.out                      > /dev/null
    lcov -a cov.baseline -a cov.out -o cov.all        > /dev/null
    lcov --extract cov.all "*armawrap*"   -o cov.all  > /dev/null
    lcov --remove  cov.all "*tests*"      -o cov.all  > /dev/null
    lcov --remove  cov.all "*armadillo*"  -o cov.all  > /dev/null
    report=`lcov --list    cov.all`

    echo "$report"

    ncovered=`echo "$report" | grep ".hpp" | wc -l`
    ntotal=$(ls $ARMAWRAP_INCLUDE_DIR/armawrap/*.hpp | wc -w)
    echo "$ncovered / $ntotal armawrap files covered"

  fi

  rm -f cov.* *.gcda *.gcno

  return $status
}

pushd `dirname $0` > /dev/null

echo "Compiling newmat ..."
pushd newmat > /dev/null
make clean
make
popd > /dev/null

exitcode=0


if ! dotest newmat ""; then
  exitcode=1
fi


if ! dotest armawrap "1"; then
  exitcode=1
fi

echo "Done!"
make clean
popd > /dev/null

exit $exitcode
