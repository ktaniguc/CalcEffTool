#!/bin/sh

if [ "$TestArea" = "" ] ; then
  echo "TestArea is missing. Please source setup.sh"
  exit 1
fi

if [ "$1" = "clean" ] ; then
  rm -r build
fi

if [ -d $TestArea/build ] ; then
  echo "Compiled in $TestArea/build"
else
  echo "Creating $TestArea/build ..."
  mkdir -p $TestArea/build
fi

if [ "$1" = "noCmake" ] ; then
  cd $TestArea/build && make -j8 && cd -
else
  cd $TestArea/build && cmake $TestArea && make -j8 && cd -
fi
