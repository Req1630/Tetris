#ifndef LEVEL_H
#define LEVEL_H

class CLevel
{
public:
	CLevel();
	~CLevel();

	// �`��.
	void Render();
	// ���������C�����̎擾.
	void SetDeleteLine( const int& line );
	// �u���b�N�����ɗ��Ƃ����Ԃ̎擾.
	int GetDownTime() const;

private:
	int m_Level;	// ���x��.
	int m_OldLevel;	// ���x��.
	int m_AddDeleteLine;	// ���������C���̍��v.
};

#endif	// #ifndef LEVEL_H.