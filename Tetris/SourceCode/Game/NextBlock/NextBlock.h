#ifndef NEXT_BLOCK_H
#define NEXT_BLOCK_H

#include "..\Block\BlockBase.h"

#include <memory>
#include <vector>

class CNextBlock
{
	const int RENDER_POSITION_X = 40;
public:
	CNextBlock();
	~CNextBlock();

	// �`��֐�.
	void Render();
	// �u���b�N�N���X�̎擾.
	void SetBlock( std::shared_ptr<CBlockBase> nextBlock ){ m_pBlock = nextBlock; }
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

#endif	// #ifndef NEXT_BLOCK_H.