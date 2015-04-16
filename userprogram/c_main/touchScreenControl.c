#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/fcntl.h>
#include <sys/time.h>
#include "prodefine.h"//需要启动程序
#include "line.h"//触摸为线条判断
#include "socket_java.h"//与java进程通信

//锁的标记
#define LOCK 0
#define UNLOCK 1

//左窗口和右窗口
#define LEFT 1
#define RIGHT 2
//无窗口事件
#define UNWINDOW 0

//函数定义
void event_Window();//窗口下程序事件处理
int open_TCHSR();//打开设备文件
int read_TCHSR();//读取文件数据
void event_TCHSR();
void deal_TCHSR(struct input_event* ev);


int fd = -1;//打开设备标志
int x = -1;//当前x坐标
int y = -1;//当前y坐标
int pressure = -128;//按下信息，按下时-127，离开是-128
long time;//按下的时常
int pid_window=-1;//窗口进程
int window = UNWINDOW;//打开的窗口
//打开进程队列
static pid_t prolist[500] = {0};//记录进程pid，进程栈
static int prolist_index = 0;//打开进程游标
//
pid_t pidMusic = 0;//记录音乐进程的pid
//记录一条线的x和y，调用line.h头文件的函数判断
#define MAX_SIZE 500
int x_line[MAX_SIZE];
int y_line[MAX_SIZE];
int length_line = 0;
int line = OTHER;//记录直线是什么直线
//notebook锁
int notebook_lock = UNLOCK;
//notebook通讯信息
char notebook_sign[20] = "close";//信号控制
struct coninfo info;//存储套接字等信息


//数据处理
void deal_TCHSR(struct input_event* ev)
{
	printf("deal_TCHSR is start\n");
        switch(ev->code){
		case ABS_X: x = ev->value-100000;printf("data    x  : %d\n",x);break;
		case ABS_Y: y = ev->value-100000;printf("data    y  : %d\n",y);break;
		case ABS_PRESSURE: pressure = ev->value;printf("data    pressure  : %d\n",pressure);break;
		default: break;
	}
}
//1个参数执行程序
void exec1cmd(char *p){
	execl(USINGPATH,USING,USER,USINGARGV,p,NULL);
}
//root 运行
void exec1cmdroot(char *p){
	execl(USINGPATH,USING,USERROOT,USINGARGV,p,NULL);
}
//
void event_Window()
{
	printf("event_Window\n");
	pid_t pid = -1;
	pid = fork();
	if(x > 1450){
		if(window == LEFT)
		{
			printf("左窗口程序1\n");
			if(pid==0){
				exec1cmd(LPRO1_PATH);
				//waitpid(getppid(),NULL,0); 
				exit(1);
			}
		}
		else{
			if(pid==0){
				exec1cmd(RPRO1_PATH);
				exit(1);
			}else{pidMusic = pid;pid = -1;}
		}
	}
	else if(x > 1130){
		if(window == LEFT)
                {
                        printf("左窗口程序2\n");
                        if(pid==0){
                                exec1cmd(LPRO2_PATH);
				//waitpid(getppid(),NULL,0);
                                exit(1);
                        }
			//else{
			//	
			//	prolist[prolist_index] = pid;
			//	printf("打开进程号:%d,index:%d\n",prolist[prolist_index],prolist_index);
			//	prolist_index++;
			//}
                }
                else{
			if(pid==0){
                                exec1cmd(RPRO2_PATH);
                                exit(1);
                        }else{
				pid = -1;
			}
                }
		
	}
	else if(x > 810){
		if(window == LEFT)
                {
                        printf("左窗口程序3\n");
                        if(pid==0){
                                exec1cmd(LPRO3_PATH);
				//waitpid(getppid(),NULL,0);
                                exit(1);
                        }
                }
		else{
			if(pid==0){
                                exec1cmd(RPRO3_PATH);
                                exit(1);
                        }else{pid = -1;}
		}
	}
	else if(x > 490){
		if(window == LEFT)
                {
                        printf("左窗口程序4\n");
                        if(pid==0){
                                exec1cmd(LPRO4_PATH);
				//waitpid(getppid(),NULL,0);
                                exit(1);
                        }else{pid = -1;}
                }
		else{
			if(pid==0){
                                exec1cmd(RPRO4_PATH);
                                exit(1);
                        }
		}
	}
	else{
		if(window == LEFT)
                {
                        printf("左窗口程序5\n");
                        if(pid==0){
                                exec1cmd(LPRO5_PAHT);
				//waitpid(getppid(),NULL,0);
                                exit(1);
                        }
                }else {
			if(pid == 0){
				system("sync;sync");
				exec1cmd(RPRO5_PATH);
				exit(1);
			}
		}
	}
	if(pid != -1 && pid != 0){
		//prolist[prolist_index] = pid;
		//prolist_index ++;
		printf("打开进程号:%d,index:%d\n",prolist[prolist_index-1],prolist_index);
	}
	//kill(pid_window,SIGKILL);
	pid_window = -1;
        window = UNWINDOW;
}
//事件处理
void event_TCHSR()
{
	int work = 256;
	printf("event is start, time :  %ld\n",time);
	printf("坐标为:%d , %d\n",x , y);
	pid_t pid_notebook;
	//事件1:left窗口
	if(y <= 410 && time < 1 && pid_window == -1 && y >= 0 && line == OTHER){
		printf("Task 1 is start\n");
		if((pid_window = fork()) == 0){
			execl(EVENT1_PATH,EVENT1_ARGV1,EVENT1_ARGV2,EVENT1_ARGV3,NULL);
			exit(1);
		}
		else if (pid_window != 0){
			window = LEFT;
		}
	}
	//事件2:right窗口
	else if(y >= 1560 && time < 1 && pid_window == -1 && line == OTHER){
		printf("Task 2 is start\n");
		if((pid_window = fork()) == 0){
                        execl(EVENT2_PATH,EVENT2_ARGV1,EVENT2_ARGV2,EVENT2_ARGV3,NULL);
                        exit(1);
                }
		else if (pid_window != 0){
			window = RIGHT;
		}

	}
	else if(pid_window != -1 && line == OTHER){
		if(window == LEFT){
			if(y>410){
				kill(pid_window,SIGKILL);
				pid_window = -1;
				window = UNWINDOW;
			}
			else{
				event_Window();
			}
		}
		else if(window == RIGHT){
			if(y < 1560){
				kill(pid_window,SIGKILL);
				pid_window = -1;
				window = UNWINDOW;
			}
			else{
				event_Window();
			}
		}
	}
	else if(line == DOWNLINE){
		printf("Event is line\n");
		if(notebook_lock == UNLOCK){
			notebook_lock = LOCK;//为记事本上锁
			//调用记事本进程
			if((pid_notebook = fork()) == 0){
				execl(EVENT3_PATH,EVENT3_ARGV1,EVENT3_ARGV2,EVENT3_ARGV3,NULL);
			}
		}
		else{
			notebook_lock = UNLOCK;//为记事本开锁
			//关闭记事本
			if(initSocket(&info) == -1)
				printf("init socket fail!\n");
			//设置发送信号信息
			strcpy(info.sendbuf,notebook_sign);
			info.sendsize = strlen(notebook_sign);
			if(sendSocket(&info) == -1)//发送信息
				printf("send fail!\n");
			closeSocket(&info);
		}
	}
	//int i = 0;
	//printf("index : %d ,prolist[] : \n",prolist_index);
	//for(; i < prolist_index; i ++)
	//	printf("%d ",prolist[i]);
	if(time >= 1 &&  prolist_index != 0 && pid_window == -1 && y >=810 && y <= 1160  && line == OTHER){
		printf("kill prcess");
		printf("%d\n,index:%d\n",prolist[prolist_index-1],prolist_index);
		prolist_index --;
		kill(prolist[prolist_index],SIGKILL);
	}
}
//读取设备信息
int read_TCHSR()
{
	printf("Read:[ok]\n");
	struct input_event event;
	int rd;
	int lock = UNLOCK;//0表示无锁
	struct timeval tpstart,tpend;
	while(1){
		rd = read(fd , &event, sizeof(struct input_event));
		if(rd < 0)
			printf("Read device is error!\n");
		if(EV_ABS == event.type)
			deal_TCHSR(&event);
		if(pressure == -127 && lock == UNLOCK){//按下后上锁并记录事件
			lock = LOCK;
			gettimeofday(&tpstart,NULL);
		}
		//当按下后记录直线的点
		else if(pressure == -127 && lock == LOCK){
			if(length_line < MAX_SIZE){
				x_line[length_line] = x;
				y_line[length_line] = y;
				length_line++;
			}
		}
		//按下结束后
		else if(pressure == -128 && lock == LOCK && x > -1 && y > -1 && x < 1830 && y < 1960){
			lock = UNLOCK;
			gettimeofday(&tpend,NULL);
			time = tpend.tv_sec-tpstart.tv_sec;
//			printf("time is : %ld, %ld\n",time,tpend.tv_sec-tpstart.tv_sec);
			//
			//调用函数判断是什么直线
			x_line[length_line] = '\0';
			y_line[length_line] = '\0';
			line = judge_Line(x_line,y_line,length_line);
			//处理事件
			event_TCHSR();
			//初始化
			time = 0;
			x = -1;
			y = -1;
			//初始化数组
			length_line = 0;
			//test
			switch(line){
				case UPLINE:printf("line : UPLINE\n");break;
				case DOWNLINE:printf("line : DOWNLINE\n");break;
				case LEFTLINE:printf("line : LEFTLINE\n");break;
				case RIGHTLINE:printf("line : RIGHTLINE\n");break;
				case OTHER:printf("line : OTHER\n");break;
			}
		}
	}
	return 0;
}
//打开设备
int open_TCHSR()
{
	printf("init:\n");
	if((fd = open(FILENAME,O_RDONLY)) < 0){
		printf("Fail:Open file error!\n");
		exit(1);
	}
	printf("open:[ok]\n");
	return 0;
}
int main(int argc, char *argv[])
{
	open_TCHSR();
	read_TCHSR();
	close(fd);
	return 0;
}
