/* 
OpenGL Template for INM376 / IN3005
City University London, School of Mathematics, Computer Science and Engineering
Source code drawn from a number of sources and examples, including contributions from
 - Ben Humphrey (gametutorials.com), Michal Bubner (mbsoftworks.sk), Christophe Riccio (glm.g-truc.net)
 - Christy Quinn, Sam Kellett and others

 For educational use by Department of Computer Science, City University London UK.

 This template contains a skybox, simple terrain, camera, lighting, shaders, texturing

 Potential ways to modify the code:  Add new geometry types, shaders, change the terrain, load new meshes, change the lighting, 
 different camera controls, different shaders, etc.
 
 Template version 5.0a 29/01/2017
 Dr Greg Slabaugh (gregory.slabaugh.1@city.ac.uk) 

 version 6.0a 29/01/2019
 Dr Eddie Edwards (Philip.Edwards@city.ac.uk)
*/


#include "game.h"


// Setup includes
#include "HighResolutionTimer.h"
#include "GameWindow.h"

// Game includes
#include "Camera.h"
#include "Skybox.h"
#include "Plane.h"
#include "Shaders.h"
#include "FreeTypeFont.h"
#include "Sphere.h"
#include "MatrixStack.h"
#include "OpenAssetImportMesh.h"
#include "Audio.h"
#include "CatmullRom.h"
#include "HeightMapTerrain.h"
#include "CylinderPole.h";
#include "Diamond.h";
#include "FrameBufferObject.h";
#include "Cube.h";
// Constructor
Game::Game()
{
	m_pSkybox = NULL;
	m_pCamera = NULL;
	m_pShaderPrograms = NULL;
	m_pPlanarTerrain = NULL;
	m_pFtFont = NULL;
	m_pSphere = NULL;
	m_pHighResolutionTimer = NULL;
	m_pAudio = NULL;
	m_pCatmullRom = NULL;
	m_pCoasterMesh = NULL;
	m_pHeightmapTerrain = NULL;
	m_pCylinderPole = NULL;
	m_pDiamond = NULL;
	m_pCharacterMesh = NULL;
	m_pCapeMesh = NULL;
	m_pHutMesh = NULL;
	m_pFenceMesh = NULL;
	m_pFBO = NULL;
	m_Cube = NULL;

	m_dt = 0.0;
	m_framesPerSecond = 0;
	m_frameCount = 0;
	m_elapsedTime = 0.0f;
	m_t = 0.0f;
	m_reached_end = false;
	m_currentDistance = 0.0f;
	free_view = true;
	stopLight = false;
	muteAudio = true;
	carSpeed = 0.0f;
	EnableFog = true;
	EnableTerrainShader = false;
	changeSphereTexture = true;
	changetoRailTrack = false;
}

// Destructor
Game::~Game() 
{ 
	//game objects
	delete m_pCamera;
	delete m_pSkybox;
	delete m_pPlanarTerrain;
	delete m_pFtFont;
	delete m_pSphere;
	delete m_pAudio;
	delete m_pCatmullRom;
	delete m_pCoasterMesh;
	delete m_pHeightmapTerrain;
	delete m_pCylinderPole;
	delete m_pDiamond;
	delete m_pCharacterMesh;
	delete m_pCapeMesh;
	delete m_pHutMesh;
	delete m_pFenceMesh;
	delete m_pFBO;
	delete m_Cube;

	if (m_pShaderPrograms != NULL) {
		for (unsigned int i = 0; i < m_pShaderPrograms->size(); i++)
			delete (*m_pShaderPrograms)[i];
	}
	delete m_pShaderPrograms;

	//setup objects
	delete m_pHighResolutionTimer;
}

// Initialisation:  This method only runs once at startup
void Game::Initialise() 
{
	// Set the clear colour and depth
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f);

	/// Create objects
	m_pCamera = new CCamera;
	m_pSkybox = new CSkybox;
	m_pShaderPrograms = new vector <CShaderProgram *>;
	m_pPlanarTerrain = new CPlane;
	m_pFtFont = new CFreeTypeFont;
	m_pSphere = new CSphere;
	m_pAudio = new CAudio;
	m_pCatmullRom = new CCatmullRom;
	m_pCoasterMesh = new COpenAssetImportMesh;
	m_pHeightmapTerrain = new CHeightMapTerrain;
	m_pCylinderPole = new CCylinder;
	m_pDiamond = new Diamond;
	m_pCharacterMesh = new COpenAssetImportMesh;
	m_pCapeMesh = new COpenAssetImportMesh;
	m_pHutMesh = new COpenAssetImportMesh;
	m_pFenceMesh = new COpenAssetImportMesh;
	m_pFBO = new CFrameBufferObject;
	m_Cube = new CCube;

	RECT dimensions = m_gameWindow.GetDimensions();

	int width = dimensions.right - dimensions.left;
	int height = dimensions.bottom - dimensions.top;

	// Set the orthographic and perspective projection matrices based on the image size
	m_pCamera->SetOrthographicProjectionMatrix(width, height); 
	m_pCamera->SetPerspectiveProjectionMatrix(45.0f, (float) width / (float) height, 0.5f, 5000.0f);

	// Load shaders
	vector<CShader> shShaders;
	vector<string> sShaderFileNames;
	sShaderFileNames.push_back("mainShader.vert");
	sShaderFileNames.push_back("mainShader.frag");
	sShaderFileNames.push_back("textShader.vert");
	sShaderFileNames.push_back("textShader.frag");
	sShaderFileNames.push_back("terrainshader.vert");
	sShaderFileNames.push_back("terrainshader.frag");
	sShaderFileNames.push_back("sphereShader.vert");
	sShaderFileNames.push_back("SphereShader.frag");
	sShaderFileNames.push_back("track.vert");
	sShaderFileNames.push_back("track.frag");
	sShaderFileNames.push_back("batman.vert");
	sShaderFileNames.push_back("batman.frag");
	sShaderFileNames.push_back("diamond.vert");
	sShaderFileNames.push_back("diamond.frag");

	for (int i = 0; i < (int) sShaderFileNames.size(); i++) {
		string sExt = sShaderFileNames[i].substr((int) sShaderFileNames[i].size()-4, 4);
		int iShaderType;
		if (sExt == "vert") iShaderType = GL_VERTEX_SHADER;
		else if (sExt == "frag") iShaderType = GL_FRAGMENT_SHADER;
		else if (sExt == "geom") iShaderType = GL_GEOMETRY_SHADER;
		else if (sExt == "tcnl") iShaderType = GL_TESS_CONTROL_SHADER;
		else iShaderType = GL_TESS_EVALUATION_SHADER;
		CShader shader;
		shader.LoadShader("resources\\shaders\\"+sShaderFileNames[i], iShaderType);
		shShaders.push_back(shader);
	}

	// Create the main shader program
	CShaderProgram *pMainProgram = new CShaderProgram;
	CreateProg(pMainProgram, 0, shShaders);
	m_pShaderPrograms->push_back(pMainProgram);

	// Create a shader program for fonts
	CShaderProgram *pFontProgram = new CShaderProgram;
	CreateProg(pFontProgram, 2, shShaders);
	m_pShaderPrograms->push_back(pFontProgram);

	// Create a shader program for the terrain
	CShaderProgram* pTerrainProgram = new CShaderProgram;
	CreateProg(pTerrainProgram, 4, shShaders);
	m_pShaderPrograms->push_back(pTerrainProgram);

	// Create a shader program for the sphere
	CShaderProgram* pSphereProgram = new CShaderProgram;
	CreateProg(pSphereProgram, 6, shShaders);
	m_pShaderPrograms->push_back(pSphereProgram);

	// Create a shader program for the track
	CShaderProgram* pTrackProgram = new CShaderProgram;
	CreateProg(pTrackProgram, 8, shShaders);
	m_pShaderPrograms->push_back(pTrackProgram);

	// Create a shader program for the Batman
	CShaderProgram* pBatmanProgram = new CShaderProgram;
	CreateProg(pBatmanProgram, 10, shShaders);
	m_pShaderPrograms->push_back(pBatmanProgram);

	// Create a shader program for the Batman
	CShaderProgram* pDiamondProgram = new CShaderProgram;
	CreateProg(pDiamondProgram, 12, shShaders);
	m_pShaderPrograms->push_back(pDiamondProgram);

	// You can follow this pattern to load additional shaders

	// Create the skybox
	m_pSkybox->Create(2500.0f);
	
	// Create the planar terrain
	m_pPlanarTerrain->Create("resources\\textures\\", "volcano.jpg", 2000.0f, 2000.0f, 10.0f); // Texture downloaded from http://www.psionicgames.com/?page_id=26 on 24 Jan 2013

	m_pFtFont->LoadSystemFont("arial.ttf", 32);
	m_pFtFont->SetShaderProgram(pFontProgram);

	//Create the coaster
	m_pCoasterMesh->Load("resources\\models\\Coaster\\Coaster.obj");  // Downloaded from http://www.psionicgames.com/?page_id=24 on 24 Jan 2013

	//Character Model
	m_pCharacterMesh->Load("resources\\models\\Batman.obj");
	m_pCapeMesh->Load("resources\\models\\Batman\\Cape.obj");

	//Start Hut
	m_pHutMesh->Load("resources\\models\\Gate\\gate.obj");

	//Create rock
	m_pFenceMesh->Load("resources\\models\\Fence\\fence.obj");

	// Create a sphere
	m_pSphere->Create("resources\\textures\\", "dirtpile01.jpg", 25, 25);  // Texture downloaded from http://www.psionicgames.com/?page_id=26 on 24 Jan 2013
	glEnable(GL_CULL_FACE);

	//Create a Cylinder Pole for Tracks
	m_pCylinderPole->TextureLoad("resources\\textures\\", "Pole.jpg");
	m_pCylinderPole->Create(248.0f, 2.0f, 5.0f); 
	m_pCylinderPole->Create(248.0f, 2.0f, 5.0f); 
	glDisable(GL_CULL_FACE);

	// Initialise audio and play background music
	m_pAudio->Initialise();
	//m_pAudio->LoadEventSound("resources\\Audio\\Boing.wav");					// Royalty free sound from freesound.org
	m_pAudio->LoadMusicStream("resources\\Audio\\Miami Disco.mp3");	// Royalty free music from http://www.nosoapradio.us/

	//Create the Diamond
	m_pDiamond->Create("resources\\textures\\", "diamond.jpg", 20.0f, 50.0f, 4.0f);

	//Create the route
	m_pCatmullRom->CreateCentreline();
	m_pCatmullRom->CreateOffsetCurves(10.f);
	m_pCatmullRom->CreateTrackRails("resources\\textures\\", "Rails.jpg",1.f);
	m_pCatmullRom->CreateTrackBars("resources\\textures\\", "Wood.jpg", 1.f);

	//Create FBO
	m_pFBO->Create(width, height);

	//Create Cube
	m_Cube->Create("resources\\textures\\", "Wood.jpg", 100.0f, 3.0f, 10.0f, 5);

	//Ambient Colors
	ambientColor.push_back(glm::vec3(1, 0, 0));//Red
	ambientColor.push_back(glm::vec3(0, 1, 0));//Green
	ambientColor.push_back(glm::vec3(0, 0, 1));//Blue
	ambientColor.push_back(glm::vec3(1, 1, 0));//Yellow
	ambientColor.push_back(glm::vec3(0, 1, 1));//Cyan
	ambientColor.push_back(glm::vec3(1, 0, 1));//Magenta
	ambientColor.push_back(glm::vec3(0.4, 0.8, 0.5));//AquaMarine
	ambientColor.push_back(glm::vec3(0.6, 0.3, 0.6));//BlueViolet
	ambientColor.push_back(glm::vec3(0.1, 0.8, 0.1));//LimeGreen
	ambientColor.push_back(glm::vec3(1, 0.1, 0.6));//Pink
	ambientColor.push_back(glm::vec3(0, 0, 0));//Black

}

void Game::Render()
{

		m_pFBO->Bind();
		RenderScene(0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		RenderScene(1);

		// Draw the 2D graphics after the 3D graphics
		DisplayFrameRate(1);
	
	// Swap buffers to show the rendered image
	SwapBuffers(m_gameWindow.Hdc());
}
// Render method runs repeatedly in a loop
void Game::RenderScene(int pass) 
{
	// Clear the buffers and enable depth testing (z-buffering)
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// Set up a matrix stack
	glutil::MatrixStack modelViewMatrixStack;
	modelViewMatrixStack.SetIdentity();

	glm::mat4 viewMatrix;
	glm::mat3 viewNormalMatrix;
	if (gameplay == 1)
	{
		//Creating all programs
		CShaderProgram* pMainProgram = (*m_pShaderPrograms)[0];
		CShaderProgram* pTerrainProgram = (*m_pShaderPrograms)[2];
		CShaderProgram* pSphereProgram = (*m_pShaderPrograms)[3];
		CShaderProgram* pTrackProgram = (*m_pShaderPrograms)[4];
		CShaderProgram* pBatmanProgram = (*m_pShaderPrograms)[5];
		CShaderProgram* pDiamondProgram = (*m_pShaderPrograms)[6];

		// Use the main shader program 
		SwitchProg(pMainProgram);
		pMainProgram->SetUniform("bUseTexture", true);
		pMainProgram->SetUniform("sampler0", 0);
		// Note: cubemap and non-cubemap textures should not be mixed in the same texture unit.  Setting unit 10 to be a cubemap texture.
		int cubeMapTextureUnit = 10;
		pMainProgram->SetUniform("CubeMapTex", cubeMapTextureUnit);


		// Set the projection matrix
		pMainProgram->SetUniform("matrices.projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());


		// Call LookAt to create the view matrix and put this on the modelViewMatrix stack. 
		// Store the view matrix and the normal matrix associated with the view matrix for later (they're useful for lighting -- since lighting is done in eye coordinates)
		modelViewMatrixStack.LookAt(m_pCamera->GetPosition(), m_pCamera->GetView(), m_pCamera->GetUpVector());
		glm::mat4 viewMatrix = modelViewMatrixStack.Top();
		glm::mat3 viewNormalMatrix = m_pCamera->ComputeNormalMatrix(viewMatrix);
		

		// Set light and materials in main shader program
		glm::vec4 lightPosition1 = glm::vec4(0, 800, 0, 1); // Position of light source *in world coordinates*
		pMainProgram->SetUniform("light1.position", viewMatrix * lightPosition1); // Position of light source *in eye coordinates*
		pMainProgram->SetUniform("light1.La", ambientColorCoord);		// Ambient colour of light
		pMainProgram->SetUniform("light1.Ld", glm::vec3(0.0f, 0.0f, 0.0f));		// Diffuse colour of light
		pMainProgram->SetUniform("light1.Ls", glm::vec3(1.0f, 1.0f, 1.0f));		// Specular colour of light
		pMainProgram->SetUniform("material1.Ma", glm::vec3(1.0f, 1.0f, 1.0f));
		pMainProgram->SetUniform("material1.Md", glm::vec3(0.0f, 0.0f, 1.0f));
		pMainProgram->SetUniform("material1.Ms", glm::vec3(1.0f, 1.0f, 1.0f));
		pMainProgram->SetUniform("material1.shininess", 1.0f);
		pMainProgram->SetUniform("fogColor", glm::vec3(0.5f, 0.5f, 0.5f));
		pMainProgram->SetUniform("fogEnable", EnableFog);

		// Render the skybox and terrain with full ambient reflectance 
		modelViewMatrixStack.Push();
		pMainProgram->SetUniform("renderSkybox", true);
		// Translate the modelview matrix to the camera eye point so skybox stays centred around camera
		glm::vec3 vEye = m_pCamera->GetPosition();
		modelViewMatrixStack.Translate(vEye);
		pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		m_pSkybox->Render(cubeMapTextureUnit);
		pMainProgram->SetUniform("renderSkybox", false);
		modelViewMatrixStack.Pop();

		if (EnableTerrainShader)
		{
			// Switch to the terrain program
			SwitchProg(pTerrainProgram);
			pTerrainProgram->SetUniform("t", 0.1f * m_t);
			pTerrainProgram->SetUniform("fogColor", glm::vec3(0.5f, 0.5f, 0.5f));
			pTerrainProgram->SetUniform("fogEnable", EnableFog);

			// Render the planar terrain
			modelViewMatrixStack.Push();
			pTerrainProgram->SetUniform("matrices.projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
			pTerrainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
			pTerrainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
			m_pPlanarTerrain->Render();
			modelViewMatrixStack.Pop();
		}
		else
		{
			// Render the planar terrain
			modelViewMatrixStack.Push();
			pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
			pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
			m_pPlanarTerrain->Render();
			modelViewMatrixStack.Pop();
		}

		// Switch to the main program
		SwitchProg(pMainProgram);

		// Turn on diffuse + specular materials
		pMainProgram->SetUniform("material1.Ma", glm::vec3(0.5f));	// Ambient material reflectance
		pMainProgram->SetUniform("material1.Md", glm::vec3(0.5f));	// Diffuse material reflectance
		pMainProgram->SetUniform("material1.Ms", glm::vec3(1.0f));	// Specular material reflectance

		// Render the CylinderPole

		glm::vec3 CylinderCoord[21]
		{
			glm::vec3(434.0f, 195.0f, -545.0f),
			glm::vec3(478, 200.0f, -309.0f),
			glm::vec3(380, 215.0f, -323.0f),
			glm::vec3(246, 225.0f, -448.0f),
			glm::vec3(-47, -228, -202),
			glm::vec3(-280, -204, -260),
			glm::vec3(-592, -47, 447),
			glm::vec3(-388, -33, 489),
			glm::vec3(-428, -79, 338),
			glm::vec3(-144, -30, 153),
			glm::vec3(-246, -100, 220),
			glm::vec3(-283, -205, 261),
			glm::vec3(-37, -171, 302),
			glm::vec3(263, -203, 277),
			glm::vec3(316, -219, 89),
			glm::vec3(19, -16, -499),
			glm::vec3(-91, -229, -87),
			glm::vec3(-254, 240, -80),
			glm::vec3(-527, 240, 2),
			glm::vec3(-345, 240, 83),
			glm::vec3(-507, 240, 237)
		};

		for (size_t i = 0; i < 21; i++)
		{
			modelViewMatrixStack.Push();
			modelViewMatrixStack.Translate(CylinderCoord[i]);
			modelViewMatrixStack.Scale(2.0f);
			pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
			pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
			m_pCylinderPole->Render();
			modelViewMatrixStack.Pop();
		}

		//Render Railway like Track
		if (changetoRailTrack)
		{
			for (size_t i = 0; i < m_pCatmullRom->m_controlPoints.size(); i++)
			{
				if (i % 5 == 0)
				{
					glm::vec3 T = glm::normalize(m_pCatmullRom->m_controlPoints[i + 1] - m_pCatmullRom->m_controlPoints[i]);
					glm::vec3 N = glm::normalize(glm::cross(T, m_pCatmullRom->m_controlUpVectors[i]));
					glm::vec3 B = glm::normalize(glm::cross(N, T));

					glm::mat4 trackOrientationaxis = glm::mat4(glm::mat3(T, B, N));

					modelViewMatrixStack.Push();
					modelViewMatrixStack.Translate(m_pCatmullRom->m_controlPoints[i] + glm::vec3(0, -1, 0));
					modelViewMatrixStack *= trackOrientationaxis;
					modelViewMatrixStack.Rotate(glm::vec3(0, 1, 0), 180.65f);
					modelViewMatrixStack.Scale(0.5f);
					pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
					pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
					m_Cube->Render();
					modelViewMatrixStack.Pop();
				}
			}
		}
		else
		{
			SwitchProg(pTrackProgram);
			m_pCatmullRom->RenderTrackBars();
		}

		SwitchProg(pMainProgram);

		//Render the coaster
		modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(coasterPos);
		modelViewMatrixStack *= coasterOrientationaxis;
		modelViewMatrixStack.Rotate(glm::vec3(0, -1, 0), 180.65f);
		modelViewMatrixStack.Scale(20.0f);
		pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		m_pCoasterMesh->Render();
		modelViewMatrixStack.Pop();

		// Render the Fence Model
		glm::vec3 Fencecoords[16]
		{
			//Back
			glm::vec3(785, 90.0f, 1000.0f),
			glm::vec3(465, 90.0f, 1000.0f),
			glm::vec3(-785, 90.0f, 1000.0f),
			glm::vec3(-400, 90.0f, 1000.0f),

			//Front
			glm::vec3(785, 90.0f, -1000.0f),
			glm::vec3(465, 90.0f, -1000.0f),
			glm::vec3(-785, 90.0f, -1000.0f),
			glm::vec3(-400, 90.0f, -1000.0f),

			//Left
			glm::vec3(1000, 90.0f, 785),
			glm::vec3(1000, 90.0f, 465),
			glm::vec3(1000, 90.0f, -785),
			glm::vec3(1000, 90.0f, -400),

			//Right
			glm::vec3(-1000, 90.0f, 785),
			glm::vec3(-1000, 90.0f, 465),
			glm::vec3(-1000, 90.0f, -785),
			glm::vec3(-1000, 90.0f, -400),
		};

		//Render the Gates
		for (size_t i = 0; i < 16; i++)
		{
			modelViewMatrixStack.Push();
			modelViewMatrixStack.Translate(Fencecoords[i % 8]);
			modelViewMatrixStack.Scale(1.0f);
			pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
			pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
			m_pFenceMesh->Render();
			modelViewMatrixStack.Pop();

			modelViewMatrixStack.Push();
			modelViewMatrixStack.Translate(Fencecoords[(i % 8) + 8]);
			modelViewMatrixStack.Rotate(glm::vec3(0, 1, 0), 180.65f);
			modelViewMatrixStack.Scale(1.0f);
			pMainProgram->SetUniform("matrices.projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
			pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
			pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
			m_pFenceMesh->Render();
			modelViewMatrixStack.Pop();
		}

		glm::vec3 gatecoords[4]
		{
			glm::vec3(37, 0.0f, 1000.0f),
			glm::vec3(37, 0.0f, -1000.0f),
			glm::vec3(1000, 0.0f, 37.0f),
			glm::vec3(-1000, 0.0f, 37.0f)
		};

		//Render the Gates
		for (size_t i = 0; i < 4; i++)
		{
			modelViewMatrixStack.Push();
			modelViewMatrixStack.Translate(gatecoords[i % 2]);
			modelViewMatrixStack.Scale(5.0f);
			pMainProgram->SetUniform("matrices.projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
			pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
			pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
			m_pHutMesh->Render();
			modelViewMatrixStack.Pop();

			modelViewMatrixStack.Push();
			modelViewMatrixStack.Translate(gatecoords[(i % 2) + 2]);
			modelViewMatrixStack.Rotate(glm::vec3(0, 1, 0), 180.65f);
			modelViewMatrixStack.Scale(5.0f);
			pMainProgram->SetUniform("matrices.projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
			pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
			pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
			m_pHutMesh->Render();
			modelViewMatrixStack.Pop();
		}

		//Render the sphere
		if (changeSphereTexture)
		{
			SwitchProg(pSphereProgram);

			// Set light and materials in main shader program
			glm::vec4 lightPosition3 = glm::vec4(0, 800, 0, 1); // Position of light source *in world coordinates*
			pSphereProgram->SetUniform("light3.position", viewMatrix * lightPosition1); // Position of light source *in eye coordinates*
			pSphereProgram->SetUniform("light3.La", ambientColorCoord);		// Ambient colour of light
			pSphereProgram->SetUniform("light3.Ld", glm::vec3(0.0f, 0.0f, 0.0f));		// Diffuse colour of light
			pSphereProgram->SetUniform("light3.Ls", glm::vec3(1.0f, 1.0f, 1.0f));		// Specular colour of light
			pSphereProgram->SetUniform("material3.Ma", glm::vec3(1.0f, 1.0f, 1.0f));
			pSphereProgram->SetUniform("material3.Md", glm::vec3(0.0f, 0.0f, 1.0f));
			pSphereProgram->SetUniform("material3.Ms", glm::vec3(1.0f, 1.0f, 1.0f));
			pSphereProgram->SetUniform("material3.shininess", 1.0f);
			pSphereProgram->SetUniform("fogColor", glm::vec3(0.5f, 0.5f, 0.5f));
			pSphereProgram->SetUniform("fogEnable", EnableFog);

			modelViewMatrixStack.Push();
			modelViewMatrixStack.Translate(glm::vec3(0.0f, 400.0f, 150.0f));
			modelViewMatrixStack.Rotate(glm::vec3(0, 1, 0), roty);
			modelViewMatrixStack.Scale(40.0f);
			pSphereProgram->SetUniform("matrices.projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
			pSphereProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
			pSphereProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
			m_pSphere->Render();
			modelViewMatrixStack.Pop();
		}
		else
		{
			if (pass == 1)
			{
				modelViewMatrixStack.Push();
				modelViewMatrixStack.Translate(glm::vec3(0.0f, 400.0f, 150.0f));
				modelViewMatrixStack.Rotate(glm::vec3(0, 1, 0), roty);
				modelViewMatrixStack.Scale(40.0f);
				pMainProgram->SetUniform("matrices.projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
				pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
				pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
				m_pFBO->BindTexture(0);
				m_pSphere->Render();
				modelViewMatrixStack.Pop();
			}
		}

		//Switch to Batman Program
		SwitchProg(pBatmanProgram);

		glm::vec4 lightPosition3 = glm::vec4(0, 600, 0, 1); // Position of light source *in world coordinates*
		pBatmanProgram->SetUniform("light3.position", viewMatrix * lightPosition3); // Position of light source *in eye coordinates*
		pBatmanProgram->SetUniform("light3.La", glm::vec3(0.6f, 0.3f, 0.6f));		// Ambient colour of light
		pBatmanProgram->SetUniform("light3.Ld", glm::vec3(0.6f, 0.3f, 0.6f));		// Diffuse colour of light
		pBatmanProgram->SetUniform("light3.Ls", glm::vec3(0.6f, 0.3f, 0.6f));		// Specular colour of light
		pBatmanProgram->SetUniform("light3.direction", glm::normalize(viewNormalMatrix * glm::vec3(0, -1, 0)));
		pBatmanProgram->SetUniform("light3.exponent", 20.0f);
		pBatmanProgram->SetUniform("light3.cutoff", 130.0f);
		pBatmanProgram->SetUniform("material3.Ma", glm::vec3(0.2f, 0.2f, 0.2f));
		pBatmanProgram->SetUniform("material3.Md", glm::vec3(1.0f, 1.0f, 1.0f));
		pBatmanProgram->SetUniform("material3.Ms", glm::vec3(1.0f, 1.0f, 1.0f));
		pBatmanProgram->SetUniform("material3.shininess", 1.0f);
		pBatmanProgram->SetUniform("t", 0.1f * m_t);
		pBatmanProgram->SetUniform("fogEnable", EnableFog);
		pBatmanProgram->SetUniform("fogColor", glm::vec3(0.5f, 0.5f, 0.5f));

		// Render the Character Model
		modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(0, 0.0f, 0.0f));
		modelViewMatrixStack.Scale(2.0f);
		pBatmanProgram->SetUniform("sampler0", 0);
		pBatmanProgram->SetUniform("bUseTexture", true); // turn off texturing
		pBatmanProgram->SetUniform("matrices.projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
		pBatmanProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pBatmanProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		m_pCharacterMesh->Render();
		m_pCapeMesh->Render();
		modelViewMatrixStack.Pop();

		//Switch to Diamond Program
		SwitchProg(pDiamondProgram);

		glm::vec4 lightPosition4 = glm::vec4(-480, 800.0f, 125.0f, 1); // Position of light source *in world coordinates*
		pDiamondProgram->SetUniform("light4.position", viewMatrix * lightPosition3); // Position of light source *in eye coordinates*
		pDiamondProgram->SetUniform("light4.La", glm::vec3(1.0f, 1.0f, 1.0f));		// Ambient colour of light
		pDiamondProgram->SetUniform("light4.Ld", glm::vec3(1.0f, 1.0f, 0.0f));		// Diffuse colour of light
		pDiamondProgram->SetUniform("light4.Ls", glm::vec3(1.0f, 0.0f, 0.0f));		// Specular colour of light
		pDiamondProgram->SetUniform("material4.Ma", glm::vec3(0.2f, 0.2f, 0.2f));
		pDiamondProgram->SetUniform("material4.Md", glm::vec3(1.0f, 1.0f, 1.0f));
		pDiamondProgram->SetUniform("material4.Ms", glm::vec3(1.0f, 1.0f, 1.0f));
		pDiamondProgram->SetUniform("material4.shininess", 150.0f);
		pDiamondProgram->SetUniform("fogEnable", EnableFog);
		pDiamondProgram->SetUniform("fogColor", glm::vec3(0.5f, 0.5f, 0.5f));

		// Render the Diamond
		modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(-480, 400.0f, 125.0f));
		modelViewMatrixStack.Rotate(glm::vec3(0, 1, 0), roty);
		modelViewMatrixStack.Scale(2.0f);
		pDiamondProgram->SetUniform("bUseTexture", true); // turn off texturing
		pDiamondProgram->SetUniform("matrices.projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
		pDiamondProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pDiamondProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		m_pDiamond->Render();
		modelViewMatrixStack.Pop();

		//Switch to Track Program
		SwitchProg(pTrackProgram);

		glm::vec4 lightPosition2 = glm::vec4(Lightpos, 1); // Position of light source *in world coordinates*
		pTrackProgram->SetUniform("light2.position", viewMatrix * lightPosition2); // Position of light source *in eye coordinates*
		pTrackProgram->SetUniform("light2.La", glm::vec3(0.5f));		// Ambient colour of light
		pTrackProgram->SetUniform("light2.Ld", glm::vec3(1.f));		// Diffuse colour of light
		pTrackProgram->SetUniform("light2.Ls", glm::vec3(1.f));		// Specular colour of light
		pTrackProgram->SetUniform("light2.direction", glm::normalize(viewNormalMatrix * glm::vec3(SpotlightView.x, -0.1, SpotlightView.z)));
		pTrackProgram->SetUniform("light2.exponent", 150.0f);
		pTrackProgram->SetUniform("light2.cutoff", 130.0f);
		pTrackProgram->SetUniform("FreeView", free_view);
		pTrackProgram->SetUniform("material2.Ma", ambientColorCoord);
		pTrackProgram->SetUniform("material2.Md", glm::vec3(1.0f, 1.0f, 1.0f));
		pTrackProgram->SetUniform("material2.Ms", glm::vec3(1.0f, 1.0f, 1.0f));
		pTrackProgram->SetUniform("material2.shininess", 1.0f);
		pTrackProgram->SetUniform("fogEnable", EnableFog);
		pTrackProgram->SetUniform("fogColor", glm::vec3(0.5f, 0.5f, 0.5f));

		modelViewMatrixStack.Push();
		pTrackProgram->SetUniform("sampler0", 0);
		pTrackProgram->SetUniform("bUseTexture", true); // turn off texturing
		pTrackProgram->SetUniform("matrices.projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
		pTrackProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTrackProgram->SetUniform("matrices.normalMatrix",
			m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));

		//Render the route
		m_pCatmullRom->RenderCentreline();
		m_pCatmullRom->RenderOffsetCurves();
		m_pCatmullRom->RenderTrackRails();
	}
	else
	{
		// Call LookAt to create the view matrix and put this on the modelViewMatrix stack. 
		// Store the view matrix and the normal matrix associated with the view matrix for later (they're useful for lighting -- since lighting is done in eye coordinates)
		modelViewMatrixStack.LookAt(m_pCamera->GetPosition(), m_pCamera->GetView(), m_pCamera->GetUpVector());
		viewMatrix = modelViewMatrixStack.Top();
		viewNormalMatrix = m_pCamera->ComputeNormalMatrix(viewMatrix);
		DisplayFrameRate(0);
	}
	// Draw the 2D graphics after the 3D graphics
	//DisplayFrameRate();

	// Swap buffers to show the rendered image
	//SwapBuffers(m_gameWindow.Hdc());		

}

// Update method runs repeatedly with the Render method
void Game::Update() 
{

		// Update the camera using the amount of time that has elapsed to avoid framerate dependent motion
		m_pCamera->Update(m_dt);
	if (gameplay != 0)
	{
		roty += 0.003f * m_dt;

		m_currentDistance += m_dt * carSpeed;

		m_t += (float)(0.01f * m_dt);

		if (!stopLight)
			ambientColorCoord = ambientColor[rand() % ambientColor.size()];
		else
			ambientColorCoord = glm::vec3(1, 1, 1);

		if (!muteAudio)
			m_pAudio->PlayMusicStream();

		glm::vec3 p;
		glm::vec3 pNext;
		glm::vec3 PCoaster;
		glm::vec3 up;
		glm::vec3 upNext;
		glm::vec3 upCoaster;

		m_pCatmullRom->Sample(m_currentDistance, p, up);

		m_pCatmullRom->Sample(m_currentDistance + 1.0f, pNext, upNext);

		//For Coaster
		m_pCatmullRom->Sample(m_currentDistance + 5.0f, PCoaster, upCoaster);

		glm::vec3 dir = glm::normalize(pNext - p);

		glm::vec3 T = p + (10.0f * dir);
		glm::vec3 N = glm::normalize(glm::cross(dir, up));
		glm::vec3 B = glm::normalize(glm::cross(N, dir));

		SpotlightView = dir;

		//Set the Coasters position and orientation
		coasterOrientationaxis = glm::mat4(glm::mat3(dir, B, N));

		coasterPos = PCoaster;

		Lightpos = coasterPos + (dir * 30.0f) + (B * 5.0f);

		if (!free_view)
		{
			m_pCamera->Set(p + (B * 45.0f), T + (B * 45.0f), B);

			if (left)
			{
				m_pCamera->Set(p + (B * 30.0f) - (N * 100.0f), PCoaster + glm::vec3(0, 45, 0), B);
				top = false;
				right = false;
				fps = false;
			}
			if (top)
			{
				m_pCamera->Set(p + glm::vec3(0, 30, 0) + (B * 100.0f), PCoaster + glm::vec3(0, 45, 0), B);
				right = false;
				left = false;
				fps = false;
			}
			if (right)
			{
				m_pCamera->Set(p + (B * 30.0f) + (N * 100.0f), PCoaster, B);
				top = false;
				left = false;
				fps = false;
			}
			if (fps)
			{
				m_pCamera->Set(p + (B * 120.0f) - (dir * 100.0f), T + glm::vec3(0, 45, 0), B);
				top = false;
				left = false;
				right = false;
			}
		}
		else
		{
			m_pCamera->SetUpVec(glm::vec3(0, 1, 0));
			top = false;
			left = false;
			right = false;
			fps = false;
		}

		m_pAudio->Update();
	}
}

//Switch to desired program
void Game::SwitchProg(CShaderProgram* prog)
{
	prog->UseProgram();
}

void Game::CreateProg(CShaderProgram* prog, int element, vector<CShader> shaderVec)
{
	prog->CreateProgram();
	prog->AddShaderToProgram(&shaderVec[element]);
	prog->AddShaderToProgram(&shaderVec[element + 1]);
	prog->LinkProgram();
}

void Game::DisplayFrameRate(int start)
{


	CShaderProgram *fontProgram = (*m_pShaderPrograms)[1];

	RECT dimensions = m_gameWindow.GetDimensions();
	int height = dimensions.bottom - dimensions.top;

	// Increase the elapsed time and frame counter
	m_elapsedTime += m_dt;
	m_frameCount++;

	// Now we want to subtract the current time by the last time that was stored
	// to see if the time elapsed has been over a second, which means we found our FPS.
	if (m_elapsedTime > 1000)
    {
		m_elapsedTime = 0;
		m_framesPerSecond = m_frameCount;

		// Reset the frames per second
		m_frameCount = 0;
    }

	if (m_framesPerSecond > 0) {
		// Use the font shader program and render the text
		SwitchProg(fontProgram);
		glDisable(GL_DEPTH_TEST);
		fontProgram->SetUniform("matrices.modelViewMatrix", glm::mat4(1));
		fontProgram->SetUniform("matrices.projMatrix", m_pCamera->GetOrthographicProjectionMatrix());
		fontProgram->SetUniform("vColour", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		if (gameplay != 0)
		{
			m_pFtFont->Render(20, height - 20, 20, "F: Start/Stop FreeView");
			m_pFtFont->Render(20, height - 50, 20, "R: Start/Stop view from Right");
			m_pFtFont->Render(20, height - 80, 20, "T: Start/Stop view from Top");
			m_pFtFont->Render(20, height - 110, 20, "L: Start/Stop view from Left");
			m_pFtFont->Render(20, height - 140, 20, "C: Start/Stop First Person View");
			m_pFtFont->Render(20, height - 170, 20, "P: Start/Stop v blinking lights");
			m_pFtFont->Render(20, height - 200, 20, "M: Mute/Unmute Audio");
			m_pFtFont->Render(20, height - 230, 20, "I: Increase Speed");
			m_pFtFont->Render(20, height - 260, 20, "O: Decrease Speed");
			m_pFtFont->Render(20, height - 290, 20, "U: Stop Car");
			m_pFtFont->Render(20, height - 320, 20, "E: Disable/Enable Fog");
			m_pFtFont->Render(20, height - 350, 20, "Y: Disable/Enable Terrain Pattern");
			m_pFtFont->Render(20, height - 380, 20, "Q: Disable/Enable Sphere Shader");
			m_pFtFont->Render(20, height - 410, 20, "K: Disable/Enable Track Pattern");
		}
		else
		{
			fontProgram->SetUniform("vColour", glm::vec4(0.6f, 0.3f, 0.6f, 1.0f));
			m_pFtFont->Render(10, height - 350, 80, "ROLLER COASTER SIMULATION");
			m_pFtFont->Render(350, height - 430, 80, "PRESS ENTER");
		}
	}
}

// The game loop runs repeatedly until game over
void Game::GameLoop()
{
	/*
	// Fixed timer
	dDt = pHighResolutionTimer->Elapsed();
	if (dDt > 1000.0 / (double) Game::FPS) {
		pHighResolutionTimer->Start();
		Update();
		Render();
	}
	*/
	
	
	// Variable timer
	m_pHighResolutionTimer->Start();
	Update();
	Render();
	m_dt = m_pHighResolutionTimer->Elapsed();
	

}


WPARAM Game::Execute() 
{
	m_pHighResolutionTimer = new CHighResolutionTimer;
	m_gameWindow.Init(m_hInstance);

	if(!m_gameWindow.Hdc()) {
		return 1;
	}

	Initialise();

	m_pHighResolutionTimer->Start();

	
	MSG msg;

	while(1) {													
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { 
			if(msg.message == WM_QUIT) {
				break;
			}

			TranslateMessage(&msg);	
			DispatchMessage(&msg);
		} else if (m_appActive) {
			GameLoop();
		} 
		else Sleep(200); // Do not consume processor power if application isn't active
	}

	m_gameWindow.Deinit();

	return(msg.wParam);
}

LRESULT Game::ProcessEvents(HWND window,UINT message, WPARAM w_param, LPARAM l_param) 
{
	LRESULT result = 0;

	switch (message) {


	case WM_ACTIVATE:
	{
		switch(LOWORD(w_param))
		{
			case WA_ACTIVE:
			case WA_CLICKACTIVE:
				m_appActive = true;
				m_pHighResolutionTimer->Start();
				break;
			case WA_INACTIVE:
				m_appActive = false;
				break;
		}
		break;
		}

	case WM_SIZE:
			RECT dimensions;
			GetClientRect(window, &dimensions);
			m_gameWindow.SetDimensions(dimensions);
		break;

	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(window, &ps);
		EndPaint(window, &ps);
		break;

	case WM_KEYDOWN:
		switch(w_param) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case '1':
			m_pAudio->PlayEventSound();
			break;
		case VK_F1:
			m_pAudio->PlayEventSound();
			break;
		case 'F':
			free_view = !free_view;
			break;
		/*case 'W':
			m_currentDistance += m_dt * 5.0f;
			break;*/
			if (!free_view)
			{
			case 'L':
				if (!free_view)
				{
					left = !left;
				}
				break;
			case 'R':
				if (!free_view)
				{
					right = !right;
				}
				break;
			case 'T':
				if (!free_view)
				{
					top = !top;
				}
				break;
			case 'C':
				if (!free_view)
				{
					fps = !fps;
				}
				break;
			case 'P':
				stopLight = !stopLight;
				break;
			case 'M':
				muteAudio = !muteAudio;
				break;
			case 'I':
				carSpeed = 0.5f;
				break;
			case 'O':
				carSpeed = 0.1f;
				break;
			case 'U':
				carSpeed = 0.0f;
				break;
			case 'E':
				EnableFog = !EnableFog;
				break;
			case 'Y':
				EnableTerrainShader = !EnableTerrainShader;
				break;
			case 'Q':
				changeSphereTexture = !changeSphereTexture;
				break;
			case 'K':
				changetoRailTrack = !changetoRailTrack;
				break;
			case VK_RETURN:
				gameplay = 1;
				break;
			}
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		result = DefWindowProc(window, message, w_param, l_param);
		break;
	}

	return result;
}

Game& Game::GetInstance() 
{
	static Game instance;

	return instance;
}

void Game::SetHinstance(HINSTANCE hinstance) 
{
	m_hInstance = hinstance;
}

LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	return Game::GetInstance().ProcessEvents(window, message, w_param, l_param);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, PSTR, int) 
{
	Game &game = Game::GetInstance();
	game.SetHinstance(hinstance);

	return game.Execute();
}
