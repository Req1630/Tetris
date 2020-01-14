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
	// �v���J�n.
	QueryPerformanceCounter( &GetInstance()->m_StartTime );
}

void CFrameRate::Wait()
{
	// �v���I��.
	QueryPerformanceCounter( &GetInstance()->m_FinishTime );

	LONGLONG delta = GetInstance()->m_FinishTime.QuadPart - GetInstance()->m_StartTime.QuadPart;

	// �����̏��v����.
	double deltaTime = (double)delta / (double)GetInstance()->m_FrequencyTime.QuadPart;

	// �ҋ@����.
	double restTime = 1.0 / 30.0 - deltaTime;

	if( restTime > 0.0 ) Sleep( DWORD(restTime * 1000.0) );
	
	// 1���[�v������̎��Ԃ��Z�o.
	QueryPerformanceCounter( &GetInstance()->m_LoopendTime );
	delta = GetInstance()->m_LoopendTime.QuadPart - GetInstance()->m_StartTime.QuadPart;
	deltaTime = (double)delta / (double)GetInstance()->m_FrequencyTime.QuadPart;


//	double fps = 1.0 / deltaTime;
//	std::cout << "FPS : " << fps << std::endl;
}