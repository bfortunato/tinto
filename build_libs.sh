#!/bin/bash

CURRENT_DIR=$(pwd)
TMP_DIR=${CURRENT_DIR}/.tmp
OUT_DIR=${CURRENT_DIR}/third-party/build

#cleanup
rm -rf $TMP_DIR
mkdir $TMP_DIR

#SDL
TMP_DIR=$CURRENT_DIR/.tmp/SDL2
mkdir $TMP_DIR
cd $TMP_DIR
$CURRENT_DIR/third-party/SDL2-2.0.4/configure --prefix=$OUT_DIR
make install

cd $CURRENT_DIR
rm -rf $TMP_DIR


export CFLAGS=-I${OUT_DIR}/include/SDL2
export LDFLAGS=-L${OUT_DIR}/lib


#SDL_mixer
TMP_DIR=$CURRENT_DIR/.tmp/SDL2_mixer
mkdir $TMP_DIR
cd $TMP_DIR
$CURRENT_DIR/third-party/SDL2_mixer-2.0.1/configure --prefix=$OUT_DIR
make install
mkdir $OUT_DIR/include/SDL2_mixer
cp -rf $CURRENT_DIR/third-party/SDL2_mixer-2.0.1/*.h $OUT_DIR/include/SDL2_mixer/

cd $CURRENT_DIR
rm -rf $TMP_DIR


#SDL_ttf
TMP_DIR=$CURRENT_DIR/.tmp/SDL2_ttf
mkdir $TMP_DIR
cd $TMP_DIR
$CURRENT_DIR/third-party/SDL2_ttf-2.0.14/configure --prefix=$OUT_DIR
make install
mkdir $OUT_DIR/include/SDL2_ttf
cp -rf $CURRENT_DIR/third-party/SDL2_ttf-2.0.14/*.h $OUT_DIR/include/SDL2_ttf/

cd $CURRENT_DIR
rm -rf $TMP_DIR



#SDL_image
TMP_DIR=$CURRENT_DIR/.tmp/SDL2_image
mkdir $TMP_DIR
cd $TMP_DIR
$CURRENT_DIR/third-party/SDL2_image-2.0.1/configure --prefix=$OUT_DIR
make install
mkdir $OUT_DIR/include/SDL2_image
cp -rf $CURRENT_DIR/third-party/SDL2_image-2.0.1/*.h $OUT_DIR/include/SDL2_image/

cd $CURRENT_DIR
rm -rf $TMP_DIR