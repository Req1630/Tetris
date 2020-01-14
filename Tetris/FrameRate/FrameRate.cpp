#include "FrameRate.h"

CFrameRate::CFrameRate()
	: m_FrequencyTime	()
	, m_StartTime		()
	, m_FinishTime		()
	, m_LoopendTime		()
{
}

CFrameRate::~CFrameRate()
{
}

void CFrameRate::Init()
{
	QueryPerformanceFrequency( &GetInstance()->m_FrequencyTime );
}

void CFrameRate::Start()
{
	// 計測開始.
	QueryPerformanceCounter( &GetInstance()->m_StartTime );
}

void CFrameRate::Wait()
{
	// 計測終了.
	QueryPerformanceCounter( &GetInstance()->m_FinishTime );

	LONGLONG delta = GetInstance()->m_FinishTime.QuadPart - GetInstance()->m_StartTime.QuadPart;

	// 処理の所要時間.
	double deltaTime = (double)delta / (double)GetInstance()->m_FrequencyTime.QuadPart;

	// 待機時間.
	double restTime = 1.0 / 30.0 - deltaTime;

	if( restTime > 0.0 ) Sleep( DWORD(restTime * 1000.0) );
	
	// 1ループ当たりの時間を算出.
	QueryPerformanceCounter( &GetInstance()->m_LoopendTime );
	delta = GetInstance()->m_LoopendTime.QuadPart - GetInstance()->m_StartTime.QuadPart;
	deltaTime = (double)delta / (double)GetInstance()->m_FrequencyTime.QuadPart;


//	double fps = 1.0 / deltaTime;
//	std::cout << "FPS : " << fps << std::endl;
}