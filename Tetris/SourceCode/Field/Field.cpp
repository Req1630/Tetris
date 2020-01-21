#include "Field.h"
#include "..\Console\Console.h"

#include <fstream>
#include <iostream>
#include <iterator>

CField::CField()
	: m_Field		()
	, m_Title		()
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
	auto read = []( const std::string fileName) -> std::vector<std::string>
	{
		// ファイルの読み込み.
		std::ifstream ifs( fileName );
		std::vector<std::string> field;

		if( ifs.fail() ){
			CConsole::Draw( 0, 0, fileName, " : 読み込み失敗" );
			return field;
		}
		
		// 各行の取得,
		std::string line;
		while( getline( ifs, line ) ) field.emplace_back( line );

		return field;
	};

	GetInstance()->m_Field = read( GetInstance()->FIELD_TEXT_PATH );

	// 描画範囲の高さと幅を取得,
	GetInstance()->m_FadeWidth = GetInstance()->m_Field[0].size();
	GetInstance()->m_FadeHeight = GetInstance()->m_Field.size();

	std::vector<std::string> field = read( GetInstance()->TITLE_TEXT_PATH );
	for( int y = 0; y < GetInstance()->m_FadeHeight; y++ ){
		GetInstance()->m_Title.emplace_back();
		for( int x = 0; x < GetInstance()->m_FadeWidth/2; x++ ){
			GetInstance()->m_Title[y].emplace_back( (int)field[y][x]-48 );
		}
	}
}

void CField::Render()
{
	switch( GetInstance()->m_FadeState ){
		// 初期状態.
		case CField::enFADE_STATE::None:
			for( int y = 0; y < GetInstance()->m_FadeHeight; y++ ){
				for( int x = 0; x < GetInstance()->m_FadeWidth; x += 2 ){
					CConsole::Draw( x, y, "■" );
				}
			}

			break;
		// フェードアウト(黒くなる).
		case CField::enFADE_STATE::Out:
			GetInstance()->FadeRenderOut();

			break;
		// フェードイン(明るくなる).
		case CField::enFADE_STATE::In:
			GetInstance()->FadeRenderIn();

			break;
			// フェードイン(明るくなる).
		case CField::enFADE_STATE::Title:
			for( int y = 0; y < GetInstance()->m_FadeHeight; y++ ){
				for( int x = 0; x < GetInstance()->m_FadeWidth; x += 2 ){
					switch( GetInstance()->m_Title[y][x/2] ){
						case 0:
							CConsole::SetColor( (int)enColor::H_WHITE, (int)enColor::L_WHITE );
							CConsole::Draw( x, y, "■" );
							break;
						case 1:
							CConsole::SetColor( (int)enColor::H_RED, (int)enColor::L_RED );
							CConsole::Draw( x, y, "■" );
							break;
						case 2:
							CConsole::SetColor( (int)enColor::H_YELLOW, (int)enColor::L_YELLOW );
							CConsole::Draw( x, y, "■" );
							break;
						case 3:
							CConsole::SetColor( (int)enColor::H_BLUE, (int)enColor::L_BLUE );
							CConsole::Draw( x, y, "■" );
							break;
						case 4:
							CConsole::SetColor( (int)enColor::H_GREEN, (int)enColor::L_GREEN );
							CConsole::Draw( x, y, "■" );
							break;
						case 5:
							CConsole::SetColor( (int)enColor::H_CYAN, (int)enColor::L_CYAN );
							CConsole::Draw( x, y, "■" );
							break;
						case 6:
							CConsole::SetColor( (int)enColor::H_PURPLE, (int)enColor::L_PURPLE );
							CConsole::Draw( x, y, "■" );
							break;
						case 7:
							CConsole::SetColor( (int)enColor::L_BLACK, (int)enColor::L_BLACK );
							CConsole::Draw( x, y, "■" );
							break;
						default:
							break;
					}
					
				}
			}

			break;
		// ステージの描画.
		case CField::enFADE_STATE::Not:
			/*for( int i = 0; i < m_FadeHeight; i++ )
				CConsole::Draw( 0, -i, m_Field[i] );*/

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
			CConsole::SetColor( 15, 7 );
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
			std::string s;
			s = m_Field[y][x] + m_Field[y][x+1];

			if( s == "\"" ){
				CConsole::SetColor( 15, 7 );
			} else if( s == "ﾁ" ){
				CConsole::SetColor( 0, 0 );
			} else {
				CConsole::SetColor( 7, 0 );
			}

			CConsole::Draw( x, y, m_Field[y][x], m_Field[y][x+1] );
			Sleep( 1 );
		}
	}
	// 終了したら常にフィールドの描画.
	m_FadeState = enFADE_STATE::Not;
}