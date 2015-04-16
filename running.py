#!/usr/bin/env python
'''
1.lsmod
2.rmmod module
3.make driver module
4.insmod module
5.read event
6.write event to prodefine.h
7.make userspace module
8.cp main to running/
9.running program
'''

import re
import sys
import os
from log_print import log
from read_proc import read_event
from write_tch import write_event

def lsmod_module():
    text = os.popen('lsmod | grep "touch"').readlines()
    if len(text) is not 0:
        lst = text[0].split(' ')
        return lst[0]
    else :
        return None

def rmmod_module(mod):
    result = os.system('rmmod %s' % mod)
    if result is not 0:
        log(0,'rmmod module')
    else:
        log(1,'rmmod module')

def make_driver():
    os.chdir('./driver')
    result = os.system('make')
    os.chdir('../')
    if result is not 0:
        log(0,'make driver')
    else :
        log(1,'make driver')

def insmod_module():
    os.chdir('./driver')
    result = os.system('insmod ./touchScreenDriver.ko')
    os.system('make clean')
    os.chdir('../')
    if result is not 0:
        log(0,'insmod module')
    else :
        log(1,'insmod module')

def read_e():
    log(1,'read event')
    return read_event()

def write_e(event):
    log(1,'write event')
    write_event(event)

def make_userpro():
    os.chdir('./userprogram/c_main')
    result = os.system('make;make clean')
    os.chdir('../../')
    if result is not 0:
        log(0,'make users program')
    else :
        log(1,'make users program')

def cp_main():
    result = os.system('cp ./userprogram/c_main/main ./userprogram/running/')
    if result is not 0:
        log(0,'cp main')
    else :
        log(1,'cp main')

def running_main():
    os.chdir('./userprogram/running')
    os.system('./main')

if __name__ == '__main__':
    s = lsmod_module()
    rmmod_module(s)
    make_driver()
    insmod_module()
    event = read_e()
    write_e(event)
    make_userpro()
    cp_main()
    running_main()
