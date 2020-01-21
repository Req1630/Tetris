#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "..\..\SceneBase.h"

class CStage;

class CTitleScene : public CSceneBase
{
	enum enSelect
	{
		None,

		Start	= 0,
		End		= 2,

		Max,
	};
public:
	CTitleScene( sceneManager sceneManager );
	virtual ~CTitleScene();

	virtual void Update() override;
	virtual void Render() override;

private:

	enSelect m_Select;
	enSelect m_NoSelect;
};

#endif	// #ifndef TITLE_SCENE_H.