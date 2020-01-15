#include "Field.h"
#include "..\Console\Console.h"

#include <fstream>
#include <iostream>
#include <iterator>

CField::CField()
	: m_Field		()
	, m_FadeHeight	( 0 )
	, m_FadeWidth	( 0 )
	, m_FadeState	( enFADE_STATE::None )
{
}

CField::~CField()
{
}

void CField::FieldDataRead()
{
	// �t�@�C���̓ǂݍ���.
	std::ifstream ifs( FIELD_TEXT_PATH );

	if( ifs.fail() ){
		CConsole::Draw( 0, 0, FIELD_TEXT_PATH, " : �ǂݍ��ݎ��s" );
		return;
	}

	// �e�s�̎擾,
	std::string line;
	while( getline( ifs, line ) ) m_Field.emplace_back( line );

	// �`��͈͂̍����ƕ����擾,
	m_FadeWidth = m_Field[0].size();
	m_FadeHeight = m_Field.size();
}

void CField::Render()
{
	switch( m_FadeState ){
		// �������.
		case CField::enFADE_STATE::None:
			for( int y = 0; y < m_FadeHeight; y++ ){
				for( int x = 0; x < m_FadeWidth; x += 2 ){
					CConsole::Draw( x, y, "��" );
				}
			}

			break;
		// �t�F�[�h�A�E�g(�����Ȃ�).
		case CField::enFADE_STATE::Out:
			FadeRenderOut();

			break;
		// �t�F�[�h�C��(���邭�Ȃ�).
		case CField::enFADE_STATE::In:
			FadeRenderIn();

			break;
		// �X�e�[�W�̕`��.
		case CField::enFADE_STATE::Not:
			for( int i = 0; i < m_FadeHeight; i++ )
				CConsole::Draw( 0, i, m_Field[i] );

			break;
		default:
			break;
	}
}

void CField::FadeRenderOut()
{
	// �`��͈͕̔�"��"��`�悵�Ă���.
	for( int y = 0; y < m_FadeHeight; y++ ){
		for( int x = 0; x < m_FadeWidth; x+=2 ){
			CConsole::Draw( x, y, "��" );
			Sleep( 1 );
		}
	}
}

void CField::FadeRenderIn()
{
	// �`��͈͕̔��t�B�[���h��`�悵�Ă�.
	for( int y = 0; y < m_FadeHeight; y++ ){
		for( int x = 0; x < m_FadeWidth; x+=2 ){
			CConsole::Draw( x, y, m_Field[y][x], m_Field[y][x+1] );
			Sleep( 1 );
		}
	}
	// �I���������Ƀt�B�[���h�̕`��.
	m_FadeState = enFADE_STATE::Not;
}