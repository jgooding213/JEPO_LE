#!/bin/bash

# creating the general directoruy
cd $JEPODIR/../output/

echo "Type the directory name, followed by [ENTER]:"
read -n DIR_NAME

DATE=$(date +%Y%m%d_%H%M);
IN_DIR=${DIR_NAME}_${DATE};
TARGET_DIR=$PWD/$IN_DIR;

mkdir -pv $TARGET_DIR

echo 'write your comment in README and to finish ctrl+c'
vim $TARGET_DIR/README

CONFIG=$JEPODIR/config/config_all_LYSO.cfg
cp -v $CONFIG ${TARGET_DIR}/

# loop over target positions
#for value in {-2..10..1}
for value in {0..0..1}
 do
     echo "cycle with Z pos : " $value
     
     # running the simulation
     cd $JEPODIR/build/
#     #./jepo -b --BeamYpos $value --TargYpos $value -m $JEPODIR/source/1M_event.mac
#     #./jepo -b --BeamYpos $value -m $JEPODIR/source/1M_event.mac
     ./jepo -b -c ${CONFIG} --BeamYpos $value -m $JEPODIR/source/1M_event.mac
 
done 

cd ${JEPODIR}/../output/
./summarizer.sh C-140_t ${TARGET_DIR}/all.root
