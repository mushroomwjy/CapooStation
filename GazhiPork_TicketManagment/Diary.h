#pragma once
#include "pch.h"
#include "InfoFile.h"
void DiaBuy(
	string cid, mushclock st_time,
	string starter, string destination,
	double dr_time, int price,
	int people, int sold,
	int buynum);
void DelBuy(
	string cid, mushclock st_time,
	string starter, string destination,
	double dr_time, int price,
	int people, int sold,
	int delnum);