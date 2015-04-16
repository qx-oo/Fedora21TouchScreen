#!/usr/bin/env python
'this script is output log'

def log(success_fail,message):
    if success_fail is 1:
        print 'log:message:%s\t[ok]' % message
    else:
        print 'log:message:%s\t[fail]' % message
