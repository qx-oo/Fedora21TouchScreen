#include "line.h"
int max(int *num,int length){
	int i = 0;
	int k = num[0];
	for(; i < length; i++)
		if(num[i] > k)
			k = num[i];
	return k;
}
int min(int *num,int length){
	int i = 0;
	int k = num[0];
	for(; i < length; i++)
		if(num[i] < k)
			k = num[i];
	return k;
}
//判断线条大概是直线还是横线
int judge_XY(int* x,int* y,int length){
	if(x[0] - x[length - 1] > 350){
		return DOWNLINE;
	}
	else if(x[0] - x[length - 1] < -350){
		return UPLINE;
	}
	else if(y[0] - y[length - 1] > 350){
		return LEFTLINE;
	}
	else if(y[0] - y[length - 1] < -350){
		return RIGHTLINE;
	}
	else {return OTHER;}
}
//判断线条是否是直线，返回0是，返回-1不是
int judge_String(int* a,int* b,int length){//a代表范围380的，b代表范围30的
	int i;
	if(a[0] > a[length - 1]){
		for(i = 1; i < length; i++){
			if(a[i-1] < a[i])
				return -1;
		}
	}
	else{
		for(i = 1; i < length; i++){
			if(a[i-1] > a[i])
				return -1;
		}
	}
	if(max(b,length) - min(b,length) > 40){
		return -1;
	}
	return 0;
}

//判断触摸的是什么线条
int judge_Line(int* x, int* y,int length){
	int line;
	if((line = judge_XY(x,y,length)) == OTHER)
		return OTHER;
	else if(line == DOWNLINE || line == UPLINE){
		if(judge_String(x,y,length) == -1)
			return OTHER;
		else{
			return line;
		}
	}
	else if(line == LEFTLINE || line == RIGHTLINE){
		if(judge_String(y,x,length) == -1)
			return OTHER;
		else{
			return line;
		}
	}
	return OTHER;
}
