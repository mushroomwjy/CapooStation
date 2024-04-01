#include "pch.h"
#include <time.h>
#include "InfoFile.h"

mushclock GetSysTimeMush(void) {
    time_t timep;
    struct tm* p;

    time(&timep); //��ȡ��1970������˶����룬����time_t���͵�timep
    p = localtime(&timep);//��localtime������ת��Ϊstruct tm�ṹ��

    mushclock ret;
    ret.hour = p->tm_hour;
    ret.minute = p->tm_min;

    return ret;
    //�Ѳ��Կ���OvO
}