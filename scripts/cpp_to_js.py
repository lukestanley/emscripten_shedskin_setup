#! /usr/bin/python2.7
import re
from os import system as run
from os import environ as env
import argparse

parser = argparse.ArgumentParser(description='Compiles shedskin generated cpp/hpp/Makefiles to emscripten')
parser.add_argument('-o','--outputFile', help='HTML file name to be generated', required=False)
parser.add_argument('-jslib','--js-library', help='Library to link against', required=False)
args = vars(parser.parse_args())

try:
    base_dir = env['BASEDIRECTORY']
except KeyError:
    base_dir = '~' # Applicable if you are using vagrant. Otherwise you may have to set path yourself
    print "BASEDIRECTORY environment variable not set. Assuming default : " + base_dir
    
#env['PATH'] = env['PATH']  + ':' + base_dir + 'emscripten' 

try:
    shedskin_libdir  = env['SHEDSKIN_LIBDIR'] 
except KeyError:
    shedskin_libdir  = "/usr/local/lib/python2.7/dist-packages/shedskin/lib"
    print "SHEDSKIN_LIBDIR environment variable not set. Assuming default : " + shedskin_libdir

run('sudo cp -rf ' + base_dir + '/scripts/builtin.cpp.patched ' + shedskin_libdir + '/builtin.cpp')
run('sudo cp -rf ' + base_dir + '/scripts/builtin.hpp.patched ' + shedskin_libdir + '/builtin.hpp')
run('sudo cp -rf ' + base_dir + '/scripts/complex.cpp.patched ' + shedskin_libdir + '/builtin/complex.cpp')

makefile =  open('Makefile','r').read().replace('${SHEDSKIN_LIBDIR}/re.cpp','')
lines = makefile.splitlines()

relevant_lines = []
copy_lines = False
for line in lines:
    if 'CPPFILES=' in line:
        copy_lines = True
    if 'HPPFILES=' in line:
        copy_lines = False
    if copy_lines == True:
        relevant_lines.append(line)

files = []
m = re.search(r'CPPFILES=(.*)\\',relevant_lines[0])
files.append(m.group(1))
relevant_lines.remove(relevant_lines[0])
for line in relevant_lines:
    m = re.search(r'(^.*)\\', line)
    if(m):
        files.append(m.group(1))
m = re.search(r'(\$.*)$', relevant_lines[len(relevant_lines) - 2])
files.append(m.group(1))

new_files = []
for filename in files:
    new_files.append(filename.replace('${SHEDSKIN_LIBDIR}',shedskin_libdir)) 

emscripten_cxxabi_path = base_dir + '/emscripten/system/lib/libcxxabi/include'
command = base_dir + '/' + 'emscripten/emcc -O2 '
for cpp_file in new_files:
    command = command + cpp_file
command = command + ' -I ' + shedskin_libdir + ' -I ' + emscripten_cxxabi_path
if args['js_library'] != None:
    command = command + ' --js-library ' + args['js_library']
if args['outputFile'] != None:
    command = command + ' -o ' + args['outputFile']

print command

run(command)
#run('node a.out.js')

