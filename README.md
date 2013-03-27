This repro contains a bash script that runs inside vagrant and also for ubuntu directly, setting up everything needed to see why Shedskin won't yet compile under Emscripten, and later, hopefully to ... actually compile :)

---
Usage:
---

# Install vagrant if you haven't already!

wget http://files.vagrantup.com/packages/87613ec9392d4660ffcb1d5755307136c06af08c/vagrant_i686.deb

sudo dpkg -i vagrant_i686.deb

git clone https://github.com/lukestanley/emscripten_shedskin_setup

cd emscripten_shedskin_setup/; vagrant up; vagrant ssh




This is based on https://github.com/rhelmer/emscripten-vagrant