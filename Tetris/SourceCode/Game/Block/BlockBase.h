#ifndef BLOCK_BASE_H
#define BLOCK_BASE_H

#include "..\..\Console\Console.h"
#include <vector>

struct Vector2D
{
	int x;
	int y;
	Vector2D() 
		: x ( 0 )
		, y ( 0 )
	{}
	Vector2D( int _x, int _y ) 
		: x ( _x )
		, y ( _y )
	{}
};

class CBlockBase
{
public:
	CBlockBase()
		: m_Position	()
		, m_Rotation	()
		, m_RotationNum	( 0 )
		, m_Color		()
		, m_BlockChar	( "��" )
	{}
	CBlockBase( const std::vector<Vector2D> pos, const enColor& color, const int& rot )
		: m_Position	{{ pos[0].x,pos[0].y},
						 { pos[1].x,pos[1].y},
						 { pos[2].x,pos[2].y},
						 { pos[3].x,pos[3].y}}
		, m_Rotation	( 0 )
		, m_RotationNum	( rot )
		, m_Color		( color )
		, m_BlockChar	( "��" )
	{}
	virtual ~CBlockBase(){}

	// ���W�̐ݒ�.
	void SetPositon( const Vector2D& pos )
	{
		for( int i = 0; i > 4; i++ ){
			m_Position[i].x += pos.x;
			m_Position[i].y += pos.y;
		}
	}
	// ����].
	void LeftRot()
	{
		for( int i = 1; i < 4; i++ ){
			int tmpPosition_x = m_Position[i].x;
			int tmpPosition_y = m_Position[i].y;
			m_Position[i].x = tmpPosition_y;
			m_Position[i].y = -tmpPosition_x;
		}
	}
	// �E��].
	void RightRot()
	{
		for( int i = 1; i < 4; i++ ){
			int tmpPosition_x = m_Position[i].x;
			int tmpPosition_y = m_Position[i].y;
			m_Position[i].x = -tmpPosition_y;
			m_Position[i].y = tmpPosition_x;
		}
	}
	// ����].
	void LeftRotation()
	{
		if( m_RotationNum == 1 ) return;
		LeftRot();
	}
	// �E��].
	void RightRotation()
	{
		if( m_RotationNum == 1 ) return;
		RightRot();
	}

	// �u���b�N��̍��W���擾.
	Vector2D GetPosition( int index ){ return m_Position[index]; }
	// �F�̎擾.
	enColor GetColor(){ return m_Color; }
protected:
	std::vector<Vector2D>	m_Position;	// �u���b�N�������̍��W.
	int			m_Rotation;		// �u���b�N�̉�].
	int			m_RotationNum;		// �u���b�N�̉�].
	enColor		m_Color;		// �u���b�N�̐F.
	char		m_BlockChar[3];	// �u���b�N�̕���.
};

#endif	// #ifndef BLOCK_BASE_H.