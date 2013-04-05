This repro contains a bash script that runs inside vagrant and also for ubuntu directly, setting up everything needed to see why Shedskin won't yet compile it's generated C++ output, under Emscripten. Later, hopefully it will actually compile :)


shedskin_hello_world contains a subset of the files created in the vagrant, that may be tested and built against independently. (for that one, cd into the src folder and make should show throw "fatal error:'system/include/gc_allocator.h' file not found").

---
Usage:
---

wget http://files.vagrantup.com/packages/87613ec9392d4660ffcb1d5755307136c06af08c/vagrant_i686.deb

sudo dpkg -i vagrant_i686.deb

git clone https://github.com/lukestanley/emscripten_shedskin_setup

cd emscripten_shedskin_setup/; vagrant up; vagrant ssh




This is based on https://github.com/rhelmer/emscripten-vagrant