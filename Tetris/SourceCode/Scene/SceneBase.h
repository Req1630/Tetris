#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include <memory>

class CSceneManager;
class CConsole;

class CSceneBase
{
protected:
	typedef std::shared_ptr<CSceneManager> sceneManager;

public:
	CSceneBase( sceneManager sceneManager )
		: m_pSceneManager	( sceneManager )
		, m_isGameEnd		( false )
	{
	}

	virtual ~CSceneBase(){}

	virtual void Update() = 0;
	virtual void Render() = 0;

	bool GetGameEnd() const { return m_isGameEnd; }

protected:
	CSceneBase(){}
	sceneManager m_pSceneManager;

	bool m_isGameEnd;
};

#endif	// #ifndef SCENE_BASE_H.