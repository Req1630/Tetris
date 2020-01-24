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
	// �u���b�N�N���X�̎擾.
	void SetBlock( std::shared_ptr<CBlockBase> nextBlock ){ m_pBlock = nextBlock; }
	std::shared_ptr<CBlockBase> GetBlock(){ return m_pBlock; }
	// �u���b�N�ԍ��̐ݒ�֐�.
	void SetBlockNumber( const int& number ){ m_BlockNumber = number; }
	// �u���b�N�ԍ��̎擾�֐�.
	int GetBlockNumber() const { return m_BlockNumber; }

private:
	// �����`��.
	void RenderChar( const int& x, const int& y );

private:
	std::vector<std::vector<int>>	m_BlockStage;	// �`��p�u���b�N�X�e�[�W.
	std::shared_ptr<CBlockBase>		m_pBlock;		// �`�悷��u���b�N.
	int m_BlockNumber;	// ���݂̃u���b�N�ԍ�.
};

#endif	// #ifndef HOLD_BLOCK_H.