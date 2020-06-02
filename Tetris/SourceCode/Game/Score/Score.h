#ifndef SCORE_H
#define SCORE_H

class CScore
{
	enum class enDELETE_LINE
	{
		None,

		SINGLE,
		DOUBLE,
		TRIPLE,
		TETRIS,

		MAX,
	};
	enum enADD_SCORE
	{
		None,

		SINGLE = 40,
		DOUBLE = 100,
		TRIPLE = 300,
		TETRIS = 1200,

		MAX,
	};
public:
	CScore();
	~CScore();

	// 描画.
	void Render();
	// 消したラインの取得.
	void SetDeleteLine( const int& line );

private:
	int m_Score;	// スコア.
};

#endif	// #ifndef SCORE_H.