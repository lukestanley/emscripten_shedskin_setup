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

run('cp -rf ' + base_dir + '/scripts/enginePyGame.py ./')

run('timeout 5 python ' + sys.argv[1])
