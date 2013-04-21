This repro contains a bash script that runs inside vagrant and also for ubuntu directly, setting up everything needed to compile Shedskin's subset of Python to C++ then to Javascript with Emscripten.

Built on top of this is a partial canvas implementation for Pygame, as well as for native Shedskin use, and the browser, cross-compiling among all 3 target platforms.

---
Setup like so:
---

wget http://files.vagrantup.com/packages/87613ec9392d4660ffcb1d5755307136c06af08c/vagrant_i686.deb

sudo dpkg -i vagrant_i686.deb

git clone https://github.com/lukestanley/emscripten_shedskin_setup

cd emscripten_shedskin_setup/; vagrant up

export VAGRANTDIR=$(pwd); exp="export VAGRANTDIR="; echo $exp$VAGRANTDIR >>  ~/.profile


You should find Output.html, and the test binary placed in the directory.

---
Usage:
---

$VAGRANTDIR/crosseng_js test.py

This should output Output.html to the current directory


This Vagrant setup was once loosely based on https://github.com/rhelmer/emscripten-vagrant
but it doesn't use Vagrant specific config files, in favour of more portable bash files for use without Vagrant.

