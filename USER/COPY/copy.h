#ifndef __MYCOPY_H
#define __MYCOPY_H
#include "sys.h"

typedef struct node
{
	int x;
	int y;
}my_cur;

void my_scan();
void get_infrared_value(int cur,int x,int y);
void get_line();
void cal_cur(my_cur *finall_my_cur_data);
void my_copy();
#endif