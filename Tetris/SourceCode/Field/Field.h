#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <vector>

class CField
{
	const char* FIELD_TEXT_PATH = "Data\\Field.txt";

	enum class enFADE_STATE
	{
		None,

		Out,	// �t�F�[�h�A�E�g.
		In,		// �t�F�[�h�C��.
		Not,

	};
public:
	CField();
	~CField();

	// �t�B�[���h�f�[�^�̓ǂݍ���.
	void FieldDataRead();
	// �`��.
	void Render();

	// �t�F�[�h���ĂȂ����ǂ���.
	bool IsNotFade(){ return m_FadeState == enFADE_STATE::Not? true : false; }

	// �t�F�[�h�C���̐ݒ�.
	void SetFadeIn(){ m_FadeState = enFADE_STATE::In; }
	// �t�F�[�h�A�E�g�̐ݒ�.
	void SetFadeOut(){ m_FadeState = enFADE_STATE::Out; }


private:
	// �t�F�[�h�`��.
	void FadeRenderOut();
	void FadeRenderIn();

private:
	std::vector<std::string> m_Field;	// �t�B�[���h.
	int m_FadeHeight;					// �t�F�[�h�p�̍���.
	int m_FadeWidth;					// �t�F�[�h�p�̕�.

	enFADE_STATE m_FadeState;			// ���݂̃t�F�[�h���.
};

#endif	// #ifndef FIELD_H.