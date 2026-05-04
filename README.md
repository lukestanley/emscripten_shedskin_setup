## emscripten_shedskin_setup

> **Note: This toolchain is no longer functional.** It targets Ubuntu 12.10 (EOL 2014), Vagrant v1 API, Python 2.7, and specific old versions of Shedskin and Emscripten. It is kept as a historical reference.

---

### What it was

A pipeline to run a subset of Python in the browser, built around 2012. The approach:

1. Write Python (restricted to the subset Shedskin supports — statically type-inferred, no dynamic features)
2. [Shedskin](https://github.com/shedskin/shedskin) compiles it to C++
3. [Emscripten](https://emscripten.org/) compiles that C++ to asm.js
4. The output is a self-contained HTML file

On top of this sat a partial canvas abstraction layer targeting three outputs from the same source: a native binary, a Pygame desktop app, and an HTML5 canvas in the browser. The demo is an interactive drawing app — lines and arcs following the mouse.

### Why this existed

In 2012, running Python in a browser was not straightforward:

- CPython could not compile to JavaScript
- Pyodide did not exist yet
- Emscripten was new and largely unproven

The Shedskin → Emscripten route avoided shipping an interpreter entirely: Shedskin's static type inference produced lean C++, which Emscripten turned into asm.js.

### Better options today

- [Pyodide](https://pyodide.org/) — full CPython compiled to WebAssembly
- [PyScript](https://pyscript.net/) — Python in the browser via Pyodide or MicroPython
- [pygame-ce](https://pyga.me/) — ships official WASM builds
- [Transcrypt](https://www.transcrypt.org/) — Python 3 to modern JavaScript

---

### Original setup (non-functional)

```bash
wget http://files.vagrantup.com/packages/87613ec9392d4660ffcb1d5755307136c06af08c/vagrant_i686.deb
sudo dpkg -i vagrant_i686.deb
git clone https://github.com/lukestanley/emscripten_shedskin_setup
cd emscripten_shedskin_setup/; vagrant up
export VAGRANTDIR=$(pwd); exp="export VAGRANTDIR="; echo $exp$VAGRANTDIR >> ~/.profile
```

After setup, `Output.html` and a test binary would appear in the directory.

### Original usage (non-functional)

```bash
$VAGRANTDIR/crosseng_js test.py
# outputs Output.html to the current directory
```

---

The Vagrant setup was loosely based on https://github.com/rhelmer/emscripten-vagrant but uses plain bash scripts rather than Vagrant-specific provisioning, so the scripts could also be run directly on Ubuntu.

