#!/bin/bash
if [ -d "/vagrant" ]; then
	cd ~
fi

export BASEDIRECTORY=$(pwd)

sudo apt-get -y install g++ cmake build-essential libffi-dev git openjdk-6-jdk nodejs nodejs-legacy libgc-dev libpcre++-dev libpcre3-dev

wget http://llvm.org/releases/3.2/clang+llvm-3.2-x86-linux-ubuntu-12.04.tar.gz
wget http://dl.dropbox.com/u/33191825/Patches.tar.gz
tar -xvzf Patches.tar.gz
git clone git://github.com/kripken/emscripten.git
git clone git://gitorious.org/shedskin/mainline.git
mv mainline shedskin_src
cd shedskin_src/
sudo python setup.py install
cd $BASEDIRECTORY
mkdir shedtest
cd shedtest
echo 'print "hello from shedskin"' >> hello.py
python hello.py
shedskin hello.py
make
./hello
cd $BASEDIRECTORY


tar -xvzf clang+llvm-3.2-x86-linux-ubuntu-12.04.tar.gz 

mv clang+llvm-3.2-x86-linux-ubuntu-12.04 clang_and_llvm

export PATH=$PATH:$BASEDIRECTORY/clang_and_llvm/bin
echo $PATH

mkdir llvm_test
cd llvm_test

clang $BASEDIRECTORY/emscripten/tests/hello_world.c -o hello_world

./hello_world

clang -O3 -emit-llvm $BASEDIRECTORY/emscripten/tests/hello_world.c -c -o hello_world.bc

lli hello_world.bc

export PATH=$PATH:$BASEDIRECTORY/emscripten

emcc

emcc $BASEDIRECTORY/emscripten/tests/hello_world.cpp

node a.out.js

#emcc $BASEDIRECTORY/emscripten/tests/hello_world_sdl.cpp -o hello.html


cd $BASEDIRECTORY
cp /usr/include/gc/gc_cpp.h ./emscripten/system/include/
cp /usr/include/gc/gc_allocator.h ./emscripten/system/include/

if [ -d "/vagrant" ]; then
        #cp /vagrant/shedskin_Makefile Makefile
        patch ./shedskin_src/shedskin/lib/builtin.hpp < /vagrant/builtin.hpp.patch
fi
if [ ! -d "/vagrant" ]; then
    #cp $BASEDIRECTORY/shedskin_Makefile Makefile
    patch ./shedskin_src/shedskin/lib/builtin.hpp < $BASEDIRECTORY/builtin.hpp.patch
fi


patch ./emscripten/system/include/gc_cpp.h Patches/gc_cpp.h.patch 
patch ./shedskin_src/shedskin/lib/builtin.cpp Patches/builtin.cpp.patch 
patch ./shedskin_src/shedskin/lib/builtin.hpp Patches/builtin.hpp.patch 
patch ./shedskin_src/shedskin/lib/builtin/complex.cpp Patches/complex.cpp.patch 
patch ./shedskin_src/shedskin/lib/builtin/exception.hpp Patches/exception.hpp.patch 
cd shedskin_src/
sudo python setup.py install
cd ..
mkdir shedskin_js
cd shedskin_js
echo 'print "hello from shedskin in JS"' >> hello.py
export SHEDSKIN_LIBDIR=/usr/local/lib/python2.7/dist-packages/shedskin/lib
shedskin hello.py
rm Makefile



export PATH=$PATH:$BASEDIRECTORY/emscripten
emcc hello.cpp $SHEDSKIN_LIBDIR/builtin.cpp -I $SHEDSKIN_LIBDIR
node a.out.js
#make




