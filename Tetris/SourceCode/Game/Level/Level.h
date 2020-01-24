#ifndef LEVEL_H
#define LEVEL_H

class CLevel
{
public:
	CLevel();
	~CLevel();

	void Render();
	void SetDeleteLine( const int& line );
	int GetDownTime() const;

private:
	int m_Level;
	int m_AddDeleteLine;
};

#endif	// #ifndef LEVEL_H.