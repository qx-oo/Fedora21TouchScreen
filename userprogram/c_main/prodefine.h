#ifndef PRODEFINE_H
#define PRODEFINE_H
//
//执行程序用户
#define USINGPATH "/usr/bin/su"
#define USING "su"
#define USER "qx-oo"
#define USERROOT "root"
#define USINGARGV "-c"
//
//执行程序
//notebook事件
#define EVENT3_PATH "/usr/bin/java"
#define EVENT3_ARGV1 "java"
#define EVENT3_ARGV2 "-jar"
#define EVENT3_ARGV3 "./notebook.jar"
//事件1(left window)
#define EVENT1_PATH "/usr/bin/java"
#define EVENT1_ARGV1 "java"
#define EVENT1_ARGV2 "-jar"
#define EVENT1_ARGV3 "./window_left.jar"
//事件2(right window)
#define EVENT2_PATH "/usr/bin/java"
#define EVENT2_ARGV1 "java"
#define EVENT2_ARGV2 "-jar"
#define EVENT2_ARGV3 "./window_right.jar"
//left window程序
//terminal
#define LPRO1_PATH "/usr/bin/gnome-terminal"
//mail
#define LPRO2_PATH "/usr/bin/thunderbird"
//Document
#define LPRO3_PATH "/usr/bin/nautilus --browser"
//firefox
#define LPRO4_PATH "/usr/bin/firefox"
//python scapy类库
#define LPRO5_PAHT "/usr/bin/gedit"
//right window程序
//music
//#define RPRO1_PAHT "/usr/bin/rhythmbox"
#define RPRO1_PATH "/usr/bin/rhythmbox-client --play-pause"
//music play or stop
#define RPRO2_PATH "/usr/bin/rhythmbox-client --play-pause"
//music previous
#define RPRO3_PATH "/usr/bin/rhythmbox-client --previous"
//music next
#define RPRO4_PATH "/usr/bin/rhythmbox-client --next"
//shutdown computer
#define RPRO5_PATH "/usr/bin/poweroff"
//打开的设别名称
#define FILENAME "/dev/input/event15"

#endif
