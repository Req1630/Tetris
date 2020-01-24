#ifndef HOLD_BLOCK_H
#define HOLD_BLOCK_H

#include "..\Block\BlockBase.h"

#include <memory>
#include <vector>

class CHoldBlock
{
	const int RENDER_POSITION_X = 4;
public:
	CHoldBlock();
	~CHoldBlock();

	void Render();
	// ブロッククラスの取得.
	void SetBlock( std::shared_ptr<CBlockBase> nextBlock ){ m_pBlock = nextBlock; }
	std::shared_ptr<CBlockBase> GetBlock(){ return m_pBlock; }
	// ブロック番号の設定関数.
	void SetBlockNumber( const int& number ){ m_BlockNumber = number; }
	// ブロック番号の取得関数.
	int GetBlockNumber() const { return m_BlockNumber; }

private:
	// 文字描画.
	void RenderChar( const int& x, const int& y );

private:
	std::vector<std::vector<int>>	m_BlockStage;	// 描画用ブロックステージ.
	std::shared_ptr<CBlockBase>		m_pBlock;		// 描画するブロック.
	int m_BlockNumber;	// 現在のブロック番号.
};

#endif	// #ifndef HOLD_BLOCK_H.