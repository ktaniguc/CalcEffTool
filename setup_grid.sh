#!/bin/sh
if [[ -d build ]]; then
  echo "source build/*/setup.sh  ...."
  source build/*/setup.sh
  lsetup emi
  lsetup panda
  echo 'do not forget type "voms-proxy-init -voms atlas"'
else 
  echo "there is no build directory, please compile at first ...."
fi
