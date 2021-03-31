#pragma once
#include "Common.h"
#include "vertexBufferObject.h"
#include "vertexBufferObjectIndexed.h"
#include "Texture.h"


class CCatmullRom
{
public:
	CCatmullRom();
	~CCatmullRom();

	void TextureLoad(CTexture);

	void CreateCentreline();
	void RenderCentreline();

	void CreateOffsetCurves(float textureRepeat);
	void RenderOffsetCurves();

	void CreateTrackBars(string directory, string filename,float textureRepeat);
	void RenderTrackBars();

	void CreateTrackRails(string directory, string filename,float textureRepeat);
	void RenderTrackRails();

	int CurrentLap(float d); // Return the currvent lap (starting from 0) based on distance along the control curve.

	glm::vec3 CalculateTNB(glm::vec3 Next, int element);

	void BufferAttribFunc(GLuint VAO);

	void BufferObjectFunc(CVertexBufferObject VBO);

	void AddtoVBO(CVertexBufferObject VBO, glm::vec3 points, glm::vec2 texCoord, glm::vec3 normal);

	void VAOUploadToGPU(CVertexBufferObject VBO);

	bool Sample(float d, glm::vec3& p, glm::vec3& up = _dummy_vector); // Return a point on the centreline based on a certain distance along the control curve.

	vector<glm::vec3> m_centrelinePoints;	// Centreline points

	vector<glm::vec3> m_controlPoints;		// Control points, which are interpolated to produce the centreline points

	vector<glm::vec3> m_controlUpVectors;	// Control upvectors, which are interpolated to produce the centreline upvectors

private:

	void SetControlPoints();
	void ComputeLengthsAlongControlPoints();
	void UniformlySampleControlPoints(int numSamples);
	glm::vec3 Interpolate(glm::vec3& p0, glm::vec3& p1, glm::vec3& p2, glm::vec3& p3, float t);


	vector<float> m_distances;
	CTexture m_textureRails;
	CTexture m_textureBars;

	GLuint m_vaoCentreline;
	GLuint m_vaoLeftOffsetCurveforTopBorder;
	GLuint m_vaoRightOffsetCurveforTopBorder;
	GLuint m_vaoLeftOffsetCurveforCentreline;
	GLuint m_vaoRightOffsetCurveforCentreline;
	GLuint m_vaoLeftOffsetCurveforborder;
	GLuint m_vaoRightOffsetCurveforborder;
	GLuint m_vaoTrackLeft;
	GLuint m_vaoTrackRight;
	GLuint m_vaoTrackforCentreLine;
	GLuint m_vaoTrackforLeftBorder;
	GLuint m_vaoTrackforRightBorder;

	static glm::vec3 _dummy_vector;
	vector<glm::vec3> m_centrelineUpVectors;// Centreline upvectors

	vector<glm::vec3> m_leftOffsetPointsforTopBorder;	// Left offset curve points
	vector<glm::vec3> m_rightOffsetPointsforTopBorder;	// Right offset curve points
	vector<glm::vec3> m_leftOffsetPointsforCentreline;	// Left offset curve points
	vector<glm::vec3> m_rightOffsetPointsforCentreline;	// Right offset curve points
	vector<glm::vec3> m_leftOffsetPointsforborder;	// Left offset curve points
	vector<glm::vec3> m_rightOffsetPointsforborder;	// Right offset curve points

	unsigned int m_vertexCount;				// Number of vertices in the track VBO
};
