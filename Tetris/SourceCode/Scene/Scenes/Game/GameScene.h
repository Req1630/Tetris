#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "..\..\SceneBase.h"

class CGameScene : public CSceneBase
{
public:
	CGameScene( sceneManager sceneManager );
	virtual ~CGameScene();

	virtual void Update() override;
	virtual void Render() override;
};

#endif	// #ifndef GAME_SCENE_H.