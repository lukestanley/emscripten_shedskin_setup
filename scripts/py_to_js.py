#! /usr/bin/python2.7

from os import system as run
from os import environ as env
import sys

try:
    base_dir = env['BASEDIRECTORY']
except KeyError:
    base_dir = '~' # Applicable if you are using vagrant. Otherwise you may have to set path yourself
    print "BASEDIRECTORY environment variable not set. Assuming default : " + base_dir

if len(sys.argv) != 2:
    print 'Incorrect number of arguments. Please enter the python script as argument'

# Converting Py to C++ using shedskin
run( base_dir + '/scripts/' +'py_to_cpp.py ' + sys.argv[1])

# Converting  C++ to JS using emscripten
run( base_dir + '/scripts/' +'cpp_to_js.py')

