#! /usr/bin/python2.7
import re
from os import system as run
from os import environ as env
import sys

if len(sys.argv) != 2:
    print 'Incorrect number of arguments. Please enter the python script as argument'

try:
    base_dir = env['BASEDIRECTORY']
except KeyError:
    base_dir = '~' # Applicable if you are using vagrant. Otherwise you may have to set path yourself
    print "BASEDIRECTORY environment variable not set. Assuming default : " + base_dir

try:
    shedskin_libdir  = env['SHEDSKIN_LIBDIR'] 
except KeyError:
    shedskin_libdir  = "/usr/local/lib/python2.7/dist-packages/shedskin/lib"
    print "SHEDSKIN_LIBDIR environment variable not set. Assuming default : " + shedskin_libdir


run('sudo cp -rf ' + base_dir + '/scripts/builtin.cpp.orig ' + shedskin_libdir + '/builtin.cpp')
run('sudo cp -rf ' + base_dir + '/scripts/builtin.hpp.orig ' + shedskin_libdir + '/builtin.hpp')
run('sudo cp -rf ' + base_dir + '/scripts/complex.cpp.orig ' + shedskin_libdir + '/builtin/complex.cpp')

run('cp -rf ' + base_dir + '/scripts/engine.py ./enginePyGame.py')
run('cp -rf ' + base_dir + '/scripts/engineSDL.cpp ./')
run('cp -rf ' + base_dir + '/scripts/engineSDL.hpp ./')
run('cp -rf ' + base_dir + '/scripts/MakefileEngine.make ./')
run(base_dir + '/scripts/' +'py_to_cpp.py ' + sys.argv[1])
run('make -f MakefileEngine.make')
