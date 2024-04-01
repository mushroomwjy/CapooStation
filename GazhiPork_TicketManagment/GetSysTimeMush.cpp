#include "pch.h"
#include <time.h>
#include "InfoFile.h"

mushclock GetSysTimeMush(void) {
    time_t timep;
    struct tm* p;

    time(&timep); //获取从1970至今过了多少秒，存入time_t类型的timep
    p = localtime(&timep);//用localtime将秒数转化为struct tm结构体

    mushclock ret;
    ret.hour = p->tm_hour;
    ret.minute = p->tm_min;

    return ret;
    //已测试可用OvO
}