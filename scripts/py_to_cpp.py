#! /usr/bin/python2.7

from os import system as run
from os import environ as env
import sys

try:
    base_dir = env['BASEDIRECTORY']
except KeyError:
    base_dir = '~' # Applicable if you are using vagrant. Otherwise you may have to set path yourself

if len(sys.argv) != 2:
    print 'Incorrect number of arguments. Please enter the python script as argument'

print "Compiling the script to C++"

run('shedskin ' + sys.argv[1])
