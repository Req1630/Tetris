#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "..\..\SceneBase.h"

class CStage;
class CScore;
class CLevel;

class CGameScene : public CSceneBase
{
public:
	CGameScene( sceneManager sceneManager );
	virtual ~CGameScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	std::unique_ptr<CStage>	m_pStage;
	std::unique_ptr<CScore>	m_pScore;
	std::unique_ptr<CLevel> m_pLevel;
};

#endif	// #ifndef GAME_SCENE_H.