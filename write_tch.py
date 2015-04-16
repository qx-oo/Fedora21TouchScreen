#!/usr/bin/env python
"This module is write event* to usernamespace's prodefine.h"

import os
import re
import sys

def write_event(event):
    mch = '^#define FILENAME'
    text = os.popen('cat ./userprogram/c_main/prodefine.h').readlines()
    for i in range(len(text)):
        if re.match(mch,text[i]):
            text[i] = re.sub('event[0-9]+',event,text[i])
            break
    fl = open('./userprogram/c_main/prodefine.h', 'w')
    fl.writelines(text)
    fl.close()

if __name__ == '__main__':
    event = sys.argv[1]
    write_event(event)
