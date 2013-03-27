#!/bin/bash
export user=$(whoami)
echo $user
cd ~
touch test_in_home_of_vagrant_user


sudo apt-get -y install g++ cmake build-essential libffi-dev git openjdk-6-jdk nodejs nodejs-legacy libgc-dev libpcre++-dev libpcre3-dev

wget http://llvm.org/releases/3.2/clang+llvm-3.2-x86-linux-ubuntu-12.04.tar.gz
git clone git://github.com/kripken/emscripten.git
git clone git://gitorious.org/shedskin/mainline.git
mv mainline shedskin_src
cd shedskin_src/
sudo python setup.py install
cd ..
mkdir shedtest
cd shedtest
echo 'print "hello from shedskin"' >> hello.py
python hello.py
shedskin hello.py
make
./hello
cd ~


tar -xvzf clang+llvm-3.2-x86-linux-ubuntu-12.04.tar.gz 

mv clang+llvm-3.2-x86-linux-ubuntu-12.04 clang_and_llvm

export PATH=$PATH:~/clang_and_llvm/bin
echo $PATH
cd ~
mkdir llvm_test
cd llvm_test

clang ~/emscripten/tests/hello_world.c -o hello_world

./hello_world

clang -O3 -emit-llvm ~/emscripten/tests/hello_world.c -c -o hello_world.bc

lli hello_world.bc

export PATH=$PATH:~/emscripten

emcc

emcc ~/emscripten/tests/hello_world.cpp

node a.out.js

#emcc ~/emscripten/tests/hello_world_sdl.cpp -o hello.html


cd ~
mkdir shedskin_js
cd shedskin_js
echo 'print "hello from shedskin in JS"' >> hello.py
shedskin hello.py
rm Makefile
if [ -d "/vagrant" ]; then
	cp /vagrant/shedskin_Makefile Makefile
	patch ../shedskin_src/shedskin/lib/builtin.hpp < /vagrant/builtin.hpp.patch
fi
export PATH=$PATH:~/emscripten
make




