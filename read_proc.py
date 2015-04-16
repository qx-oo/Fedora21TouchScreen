#!/usr/bin/env python
'this is read /proc/but/input/devices and seach touch screen event'

import os
import re

def read_event():
    bl = 0
    name_match = '.*TouchController.*'
    event_match = '^H:'
    split_str = '[\s=]'
    text = os.popen('cat /proc/bus/input/devices').readlines()
    for line in text:
        if re.match(name_match,line) is None:
            pass
        else :
            bl = 1
        if re.match(event_match,line) is not None and bl is 1:
            break
    if bl is 0:
        return None
    else:
        return re.split(split_str,line)[-3:-2][0]

if __name__ == '__main__':
    lst = read_event()
    if lst is None:
        print 'Not found'
    else:
        print lst
