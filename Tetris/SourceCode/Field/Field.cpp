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
	// ファイルの読み込み.
	std::ifstream ifs( FIELD_TEXT_PATH );

	if( ifs.fail() ){
		CConsole::Draw( 0, 0, FIELD_TEXT_PATH, " : 読み込み失敗" );
		return;
	}

	// 各行の取得,
	std::string line;
	while( getline( ifs, line ) ) m_Field.emplace_back( line );

	// 描画範囲の高さと幅を取得,
	m_FadeWidth = m_Field[0].size();
	m_FadeHeight = m_Field.size();
}

void CField::Render()
{
	switch( m_FadeState ){
		// 初期状態.
		case CField::enFADE_STATE::None:
			for( int y = 0; y < m_FadeHeight; y++ ){
				for( int x = 0; x < m_FadeWidth; x += 2 ){
					CConsole::Draw( x, y, "■" );
				}
			}

			break;
		// フェードアウト(黒くなる).
		case CField::enFADE_STATE::Out:
			FadeRenderOut();

			break;
		// フェードイン(明るくなる).
		case CField::enFADE_STATE::In:
			FadeRenderIn();

			break;
		// ステージの描画.
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
	// 描画の範囲分"■"を描画していく.
	for( int y = 0; y < m_FadeHeight; y++ ){
		for( int x = 0; x < m_FadeWidth; x+=2 ){
			CConsole::Draw( x, y, "■" );
			Sleep( 1 );
		}
	}
}

void CField::FadeRenderIn()
{
	// 描画の範囲分フィールドを描画してく.
	for( int y = 0; y < m_FadeHeight; y++ ){
		for( int x = 0; x < m_FadeWidth; x+=2 ){
			CConsole::Draw( x, y, m_Field[y][x], m_Field[y][x+1] );
			Sleep( 1 );
		}
	}
	// 終了したら常にフィールドの描画.
	m_FadeState = enFADE_STATE::Not;
}