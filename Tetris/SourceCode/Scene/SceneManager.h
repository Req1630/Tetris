#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <memory>
#include <stack>

#include "SceneBase.h"

class CSceneManager
{
	typedef std::shared_ptr<CSceneBase> sceneBase;

public:
	CSceneManager(){};
	~CSceneManager(){};

	CSceneManager( sceneBase pSceneBase )
	{
		if( pSceneBase == nullptr ) return;
		m_pStackScene.push( pSceneBase );
	}

	void Update(){ m_pStackScene.top()->Update(); }

	void Render(){ m_pStackScene.top()->Render(); }

	void Change( sceneBase& pSceneBase )
	{
		m_pStackScene.pop();
		m_pStackScene.push( pSceneBase );
	}

	void Release()
	{
		size_t sceneSize = m_pStackScene.size();
		for( size_t i = 0; i < sceneSize; i++ )
			m_pStackScene.pop();
	}

private:
	std::stack<sceneBase>	m_pStackScene;

};

#endif	// #ifndef SCENE_MANAGER_H.