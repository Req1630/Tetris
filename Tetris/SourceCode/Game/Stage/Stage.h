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
	void BlockDelete();
	bool IsOverlappedBlock( int index );

private:
	int m_MainStage[HEIGHT][WIDTH];
	int m_ColorStage[HEIGHT][WIDTH];
	int m_HoldAndNextBlock[4][4];
	std::vector<std::shared_ptr<CBlockBase>>	m_Blocks;
	std::vector<std::shared_ptr<CBlockBase>>	m_NextAndHoldBlocks;
	std::shared_ptr<CBlockBase> NowBlock;
	std::shared_ptr<CBlockBase> NextBlock;
	std::shared_ptr<CBlockBase> HoldBlock;
	Vector2D					NowPosition;

	int m_BlockDownCount;
	int m_BlockResetCount;
	std::vector<int> m_BlockList;

	bool m_isPutBlock;
};

#endif	// #ifndef STAGE_H.