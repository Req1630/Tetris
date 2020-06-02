#ifndef STAGE_H
#define STAGE_H

#include "..\Block\BlockBase.h"
#include "..\NextBlock\NextBlock.h"
#include "..\HoldBlock\HoldBlock.h"

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

	// 操作関数.
	void Control();
	// 更新関数.
	void Update();
	// 描画関数.
	void Render();
	// ステージの作成.
	void CreateStage();
	// ブロックの作成.
	void CreateBlock();
	// 現在の座標.
	void InitNowPosition();
	// 消したラインの取得関数.
	int GetDeleteLine() const { return m_DeleteLine; }
	// ゲーム終了したか.
	bool GetGameEnd() const { return m_isGameEnd; }
	// 下に落とす時間の設定かんすう.
	void SetDownTime( const int& time ){ m_BlockDownTime = time; }

private:
	// 下に落とす関数.
	void BlockDown();
	// ブロックが置かれたか確認.
	void BlockPutCheck();
	// ブロックを消す関数.
	void BlockDelete();
	// ゲームオーバーか確認.
	void GameOverCheck();
	// ゲームオーバー後の描画が終わったか.
	bool GameOverRender();
	// ブロックが重なっているか.
	bool IsOverlappedBlock( const Vector2D& pos, int index );

private:
	std::vector<std::vector<int>> m_MainStage;
	std::vector<std::vector<int>> m_ColorStage;
	std::vector<std::shared_ptr<CBlockBase>>	m_Blocks;
	std::vector<std::shared_ptr<CBlockBase>>	m_NextAndHoldBlocks;
	std::shared_ptr<CBlockBase> m_NowBlock;
	Vector2D					m_NowPosition;
	Vector2D					m_AfterFallingPosition;

	std::unique_ptr<CNextBlock>	m_pNextBlock;
	std::unique_ptr<CHoldBlock>	m_pHoldBlock;

	int m_BlockDownCount;
	int m_BlockDownTime;
	int m_BlockResetCount;
	int m_NowBlockNumber;
	std::vector<int> m_BlockList;

	int m_DeleteLine;

	bool m_isPutBlock;
	bool m_isHoldBlock;
	bool m_isGameOver;
	bool m_isGameEnd;
};

#endif	// #ifndef STAGE_H.