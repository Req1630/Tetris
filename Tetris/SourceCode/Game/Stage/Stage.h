#ifndef STAGE_H
#define STAGE_H

#include "..\Block\BlockBase.h"

#include <vector>
#include <memory>

class CBlockBase;

class CStage
{
	const static int HEIGHT = 25;
	const static int WIDTH = 12;
	const int INIT_POSITION_X = 5;
	const int INIT_POSITION_Y = 2;
public:
	CStage();
	~CStage();

	void Control();
	void Update();
	void Render();
	void CreateStage();
	void CreateBlock();
	void InitNowPosition();

private:
	void BlockDown();
	void BlockPutCheck();
	void BlockDelete();
	bool IsOverlappedBlock( const Vector2D& pos, int index );

private:
	int m_MainStage[HEIGHT][WIDTH];
	int m_ColorStage[HEIGHT][WIDTH];
	int m_HoldAndNextBlock[4][4];
	std::vector<std::shared_ptr<CBlockBase>>	m_Blocks;
	std::vector<std::shared_ptr<CBlockBase>>	m_NextAndHoldBlocks;
	std::shared_ptr<CBlockBase> m_NowBlock;
	std::shared_ptr<CBlockBase> m_NextBlock;
	std::shared_ptr<CBlockBase> m_HoldBlock;
	Vector2D					m_NowPosition;
	Vector2D					m_AfterFallingPosition;

	int m_BlockDownCount;
	int m_BlockResetCount;
	int m_NowBlockNumber;
	int m_HoldBlockNumber;
	int m_NextBlockNumber;
	std::vector<int> m_BlockList;

	bool m_isPutBlock;
	bool m_isHoldBlock;
};

#endif	// #ifndef STAGE_H.