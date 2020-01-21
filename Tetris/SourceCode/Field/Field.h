#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <vector>
#include <memory>

class CField
{
	const char* FIELD_TEXT_PATH = "Data\\Field.txt";
	const char* TITLE_TEXT_PATH = "Data\\Title.txt";

	enum class enFADE_STATE
	{
		None,

		Out,	// �t�F�[�h�A�E�g.
		In,		// �t�F�[�h�C��.
		Title,
		Not,

	};
public:
	CField();
	~CField();

	static CField* GetInstance()
	{
		static std::unique_ptr<CField>instance = std::make_unique<CField>();
		return instance.get();
	}

	// �t�B�[���h�f�[�^�̓ǂݍ���.
	static void FieldDataRead();
	// �`��.
	static void Render();

	// �t�F�[�h���ĂȂ����ǂ���.
	static bool IsNotFade(){ return GetInstance()->m_FadeState == enFADE_STATE::Not? true : false; }

	// �t�F�[�h�C���̐ݒ�.
	static void SetFadeIn(){ GetInstance()->m_FadeState = enFADE_STATE::In; }
	// �t�F�[�h�A�E�g�̐ݒ�.
	static void SetFadeOut(){ GetInstance()->m_FadeState = enFADE_STATE::Out; }
	static void SetTitle(){ GetInstance()->m_FadeState = enFADE_STATE::Title; }


private:
	// �t�F�[�h�`��.
	void FadeRenderOut();
	void FadeRenderIn();

private:
	std::vector<std::string>		m_Field;	// �t�B�[���h.
	std::vector<std::vector<int>>	m_Title;	// 
	int m_FadeHeight;					// �t�F�[�h�p�̍���.
	int m_FadeWidth;					// �t�F�[�h�p�̕�.

	enFADE_STATE m_FadeState;			// ���݂̃t�F�[�h���.
};

#endif	// #ifndef FIELD_H.