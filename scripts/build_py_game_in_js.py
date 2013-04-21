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


run('cp -rf ' + base_dir + '/scripts/engine.py ./enginePyGame.py')

run(base_dir + '/scripts/' +'py_to_cpp.py ' + sys.argv[1])

run('cp -rf ' + base_dir + '/scripts/enginePyGame.cpp ./')
run('cp -rf ' + base_dir + '/scripts/enginePyGame.hpp ./')
run('cp -rf ' + base_dir + '/scripts/PYJS_Draw.hpp ./')
run('cp -rf ' + base_dir + '/scripts/library_PYJSDraw.js ./')

run(base_dir + '/scripts/' + 'cpp_to_js.py -o Output.html -jslib library_PYJSDraw.js')

