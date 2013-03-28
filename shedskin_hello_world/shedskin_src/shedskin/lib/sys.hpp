/* Copyright 2005-2011 Mark Dufour and contributors; License Expat (See LICENSE) */

#ifndef __SYS_HPP
#define __SYS_HPP

#include "builtin.hpp"

using namespace __shedskin__;
namespace __sys__ {

void __init(int argc, char **argv);

extern list<str *> *argv;
extern str *version;
extern tuple2<__ss_int, __ss_int> *version_info;
extern str *__name__, *copyright, *platform, *byteorder;
extern __ss_int hexversion, maxint, maxsize;
extern file *__ss_stdin, *__ss_stdout, *__ss_stderr;

void __ss_exit();
template<class T> void __ss_exit(T x) {
    throw new SystemExit(x);
}

void *setrecursionlimit(__ss_int limit);

} // module namespace
#endif
