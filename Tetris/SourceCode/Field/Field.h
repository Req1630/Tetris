#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <vector>

class CField
{
	const char* FIELD_TEXT_PATH = "Data\\Field.txt";
	const char* TITLE_TEXT_PATH = "Data\\Title.txt";

	enum class enFADE_STATE
	{
		None,

		Out,	// フェードアウト.
		In,		// フェードイン.
		Title,
		Not,

	};
public:
	CField();
	~CField();

	// フィールドデータの読み込み.
	void FieldDataRead();
	// 描画.
	void Render();

	// フェードしてないかどうか.
	bool IsNotFade(){ return m_FadeState == enFADE_STATE::Not? true : false; }

	// フェードインの設定.
	void SetFadeIn(){ m_FadeState = enFADE_STATE::In; }
	// フェードアウトの設定.
	void SetFadeOut(){ m_FadeState = enFADE_STATE::Out; }
	void SetTitle(){ m_FadeState = enFADE_STATE::Title; }


private:
	// フェード描画.
	void FadeRenderOut();
	void FadeRenderIn();

private:
	std::vector<std::string>		m_Field;	// フィールド.
	std::vector<std::vector<int>>	m_Title;	// 
	int m_FadeHeight;					// フェード用の高さ.
	int m_FadeWidth;					// フェード用の幅.

	enFADE_STATE m_FadeState;			// 現在のフェード状態.
};

#endif	// #ifndef FIELD_H.