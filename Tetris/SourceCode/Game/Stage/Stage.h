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
	const int INIT_POSITION_Y = -1;
public:
	CStage();
	~CStage();

	void Update();
	void Render();
	void CreateStage();
	void CreateBlock();
	void InitNowPosition();

private:
	int m_MainStage[HEIGHT][WIDTH];
	int m_ColorStage[HEIGHT][WIDTH];
	std::vector<std::shared_ptr<CBlockBase>>	m_Blocks;
	std::shared_ptr<CBlockBase> NowBlock;
	Vector2D					NowPosition;

	int m_BlockDownCount;
	int m_BlockResetCount;
	std::vector<int> m_BlockList;
};

#endif	// #ifndef STAGE_H.