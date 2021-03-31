#pragma once

#include "Common.h"
#include "GameWindow.h"

// Classes used in game.  For a new class, declare it here and provide a pointer to an object of this class below.  Then, in Game.cpp, 
// include the header.  In the Game constructor, set the pointer to NULL and in Game::Initialise, create a new object.  Don't forget to 
// delete the object in the destructor.   
class CCamera;
class CSkybox;
class CShader;
class CShaderProgram;
class CPlane;
class CFreeTypeFont;
class CHighResolutionTimer;
class CSphere;
class COpenAssetImportMesh;
class CAudio;
class CCatmullRom;
class CHeightMapTerrain;
class CCylinder;
class Diamond;
class CFrameBufferObject;
class CCube;

class Game {
private:
	// Three main methods used in the game.  Initialise runs once, while Update and Render run repeatedly in the game loop.
	void Initialise();
	void Update();
	void Render();
	void RenderScene(int pass);
	void SwitchProg(CShaderProgram* prog);

	void CreateProg(CShaderProgram* prog, int element, vector<CShader> shaderVec);

	// Pointers to game objects.  They will get allocated in Game::Initialise()
	CSkybox *m_pSkybox;
	CCamera *m_pCamera;
	vector <CShaderProgram *> *m_pShaderPrograms;
	CPlane *m_pPlanarTerrain;
	CFreeTypeFont *m_pFtFont;
	CSphere *m_pSphere;
	CHighResolutionTimer *m_pHighResolutionTimer;
	CAudio *m_pAudio;
	CCatmullRom* m_pCatmullRom;
	CHeightMapTerrain* m_pHeightmapTerrain;
	CFrameBufferObject* m_pFBO;
	CCube* m_Cube;

	COpenAssetImportMesh* m_pCoasterMesh;
	COpenAssetImportMesh* m_pCharacterMesh;
	COpenAssetImportMesh* m_pCapeMesh;
	COpenAssetImportMesh* m_pHutMesh;
	COpenAssetImportMesh* m_pFenceMesh;

	CCylinder* m_pCylinderPole;
	Diamond* m_pDiamond;

	// Some other member variables
	double m_dt;
	int m_framesPerSecond;
	bool m_appActive;
	float m_t;
	glm::vec3 coasterPos;
	float coasterOrientationangle;
	glm::mat4 coasterOrientationaxis;

	bool right;
	bool left;
	bool top;
	bool fps;
	bool stopLight;
	bool muteAudio;
	bool EnableFog;
	bool EnableTerrainShader;
	bool changeSphereTexture;
	bool changetoRailTrack;

	int gameplay;
	float roty;
	float carSpeed;
	vector<glm::vec3> ambientColor;
	glm::vec3 ambientColorCoord;
	glm::vec3 SpotlightView;
	glm::vec3 Lightpos;
	glm::vec3 trackRotAxis;

public:
	Game();
	~Game();
	static Game& GetInstance();
	LRESULT ProcessEvents(HWND window,UINT message, WPARAM w_param, LPARAM l_param);
	void SetHinstance(HINSTANCE hinstance);
	WPARAM Execute();

private:
	static const int FPS = 60;
	void DisplayFrameRate(int start);
	void GameLoop();
	GameWindow m_gameWindow;
	HINSTANCE m_hInstance;
	int m_frameCount;
	double m_elapsedTime;
	bool m_reached_end;
	float m_currentDistance;
	bool free_view;
};
