#ifndef LEVEL_H
#define LEVEL_H

class CLevel
{
public:
	CLevel();
	~CLevel();

	// 描画.
	void Render();
	// 消したライン数の取得.
	void SetDeleteLine( const int& line );
	// ブロックを下に落とす時間の取得.
	int GetDownTime() const;

private:
	int m_Level;	// レベル.
	int m_OldLevel;	// レベル.
	int m_AddDeleteLine;	// 消したラインの合計.
};

#endif	// #ifndef LEVEL_H.