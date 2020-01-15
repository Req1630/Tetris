#ifndef FRAME_RATE_H
#define FRAME_RATE_H

#include <Windows.h>
#include <iostream>

#include "..\SingletonBase\SingletonBase.h"

class CFrameRate : public std::CSingletonBase<CFrameRate>
{
public:
	CFrameRate();
	~CFrameRate();

	static void Init();
	static void Start();
	static void Wait();

private:
	LARGE_INTEGER m_FrequencyTime;
	LARGE_INTEGER m_StartTime;
	LARGE_INTEGER m_FinishTime;
	LARGE_INTEGER m_LoopendTime;
};

#endif	// #ifndef FRAME_RATE_H.