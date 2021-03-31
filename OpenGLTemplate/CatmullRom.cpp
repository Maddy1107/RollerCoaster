#include "CatmullRom.h"
#define _USE_MATH_DEFINES
#include <math.h>



CCatmullRom::CCatmullRom()
{
	m_vertexCount = 0;
}

CCatmullRom::~CCatmullRom()
{}


void CCatmullRom::TextureLoad(CTexture Rtexture)
{
	// Set parameters for texturing using sampler object
	Rtexture.SetSamplerObjectParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	Rtexture.SetSamplerObjectParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Rtexture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	Rtexture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
}

// Perform Catmull Rom spline interpolation between four points, interpolating the space between p1 and p2
glm::vec3 CCatmullRom::Interpolate(glm::vec3& p0, glm::vec3& p1, glm::vec3& p2, glm::vec3& p3, float t)
{
	float t2 = t * t;
	float t3 = t2 * t;

	glm::vec3 a = p1;
	glm::vec3 b = 0.5f * (-p0 + p2);
	glm::vec3 c = 0.5f * (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3);
	glm::vec3 d = 0.5f * (-p0 + 3.0f * p1 - 3.0f * p2 + p3);

	return a + b * t + c * t2 + d * t3;

}


void CCatmullRom::SetControlPoints()
{
	// Set control points (m_controlPoints) here, or load from disk

	// Optionally, set upvectors (m_controlUpVectors, one for each control point as well)

	m_controlPoints.push_back(glm::vec3(300, 45, 0));
	m_controlPoints.push_back(glm::vec3(271, 45, 271));
	m_controlPoints.push_back(glm::vec3(0, 80, 300));
	m_controlPoints.push_back(glm::vec3(-271, 45, 271));
	m_controlPoints.push_back(glm::vec3(-300, 45, 0));
	m_controlPoints.push_back(glm::vec3(-271, 45, -271));
	m_controlPoints.push_back(glm::vec3(0, 45, -200));
	m_controlPoints.push_back(glm::vec3(171, 450, -400));
	m_controlPoints.push_back(glm::vec3(375, 450, -529));
	m_controlPoints.push_back(glm::vec3(475, 450, -529));
	m_controlPoints.push_back(glm::vec3(511, 450, -320));
	m_controlPoints.push_back(glm::vec3(300, 450, -320));
	m_controlPoints.push_back(glm::vec3(164, 150, -147));

	////LOOP
	m_controlPoints.push_back(glm::vec3(22, 139, 108));
	m_controlPoints.push_back(glm::vec3(-50, 244, 290));
	m_controlPoints.push_back(glm::vec3(-74, 400, 333));
	m_controlPoints.push_back(glm::vec3(-35, 589, 276));
	m_controlPoints.push_back(glm::vec3(90, 655, 169));
	m_controlPoints.push_back(glm::vec3(153, 637, 90));
	m_controlPoints.push_back(glm::vec3(211, 580, -16));
	m_controlPoints.push_back(glm::vec3(265, 400, -35));
	m_controlPoints.push_back(glm::vec3(235, 244, 26));
	m_controlPoints.push_back(glm::vec3(112, 139, 124));
	//LOOP

	m_controlPoints.push_back(glm::vec3(-100, 150, 390));
	m_controlPoints.push_back(glm::vec3(-363, 222, 493));
	m_controlPoints.push_back(glm::vec3(-591, 200, 440));
	m_controlPoints.push_back(glm::vec3(-246, 150, 220));

	//Spiral
	m_controlPoints.push_back(glm::vec3(-564, 232, 69));
	m_controlPoints.push_back(glm::vec3(-506, 242, 12));
	m_controlPoints.push_back(glm::vec3(-414, 252, 25));
	m_controlPoints.push_back(glm::vec3(-363, 272, 104));

	m_controlPoints.push_back(glm::vec3(-500, 282, 221));
	m_controlPoints.push_back(glm::vec3(-564, 292, 100));
	m_controlPoints.push_back(glm::vec3(-506, 302, 10));
	m_controlPoints.push_back(glm::vec3(-414, 312, 50));
	m_controlPoints.push_back(glm::vec3(-363, 332, 104));

	m_controlPoints.push_back(glm::vec3(-500, 342, 221));
	m_controlPoints.push_back(glm::vec3(-564, 352, 100));
	m_controlPoints.push_back(glm::vec3(-506, 362, 10));
	m_controlPoints.push_back(glm::vec3(-414, 372, 50));
	m_controlPoints.push_back(glm::vec3(-363, 392, 104));

	m_controlPoints.push_back(glm::vec3(-500, 402, 221));
	m_controlPoints.push_back(glm::vec3(-564, 412, 100));
	m_controlPoints.push_back(glm::vec3(-506, 422, 10));
	m_controlPoints.push_back(glm::vec3(-414, 452, 50));
	//Spiral

	m_controlPoints.push_back(glm::vec3(-215, 472, -131));
	m_controlPoints.push_back(glm::vec3(-338, 246, -6));
	m_controlPoints.push_back(glm::vec3(-162, 212, 175));
	m_controlPoints.push_back(glm::vec3(-138, 212, 63));
	m_controlPoints.push_back(glm::vec3(-91, 20, -76));
	m_controlPoints.push_back(glm::vec3(31, 237, -501));



	//UpVectors
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 0.8, 0.2));
	m_controlUpVectors.push_back(glm::vec3(0, 0.4, 0.6));
	m_controlUpVectors.push_back(glm::vec3(0, 0.4, 0.6));
	m_controlUpVectors.push_back(glm::vec3(-1, 0.8, 0.2));
	m_controlUpVectors.push_back(glm::vec3(0, 0.4, -0.6));
	m_controlUpVectors.push_back(glm::vec3(0, 0.8, -0.2));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));

	//LOOP
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0.2, 0.8, 0));
	m_controlUpVectors.push_back(glm::vec3(0.2, 0.8, -0.4));
	m_controlUpVectors.push_back(glm::vec3(0.8, 0.2, -0.6));
	m_controlUpVectors.push_back(glm::vec3(0, -1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, -1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, -1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.8, 0.2, 0.4));
	m_controlUpVectors.push_back(glm::vec3(-0.2, 0.8, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	//LOOP

	m_controlUpVectors.push_back(glm::vec3(0, 0.8, -0.2));
	m_controlUpVectors.push_back(glm::vec3(0, 0.4, -0.6));
	m_controlUpVectors.push_back(glm::vec3(0.2, 0.6, -0.4));
	m_controlUpVectors.push_back(glm::vec3(0, 0.8, 0.2));

	//SPIRAL
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 0.8, -0.5));
	m_controlUpVectors.push_back(glm::vec3(0, 0.5, -0.9));
	//SPIRAL

	m_controlUpVectors.push_back(glm::vec3(0, 0.2, -0.5));
	m_controlUpVectors.push_back(glm::vec3(0, 0.5, 0.5));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));

}


// Determine lengths along the control points, which is the set of control points forming the closed curve
void CCatmullRom::ComputeLengthsAlongControlPoints()
{
	int M = (int)m_controlPoints.size();

	float fAccumulatedLength = 0.0f;
	m_distances.push_back(fAccumulatedLength);
	for (int i = 1; i < M; i++) {
		fAccumulatedLength += glm::distance(m_controlPoints[i - 1], m_controlPoints[i]);
		m_distances.push_back(fAccumulatedLength);
	}

	// Get the distance from the last point to the first
	fAccumulatedLength += glm::distance(m_controlPoints[M - 1], m_controlPoints[0]);
	m_distances.push_back(fAccumulatedLength);
}


// Return the point (and upvector, if control upvectors provided) based on a distance d along the control polygon
bool CCatmullRom::Sample(float d, glm::vec3& p, glm::vec3& up)
{
	if (d < 0)
		return false;

	int M = (int)m_controlPoints.size();
	if (M == 0)
		return false;


	float fTotalLength = m_distances[m_distances.size() - 1];

	// The the current length along the control polygon; handle the case where we've looped around the track
	float fLength = d - (int)(d / fTotalLength) * fTotalLength;

	// Find the current segment
	int j = -1;
	for (int i = 0; i < (int)m_distances.size() - 1; i++) {
		if (fLength >= m_distances[i] && fLength < m_distances[i + 1]) {
			j = i; // found it!
			break;
		}
	}

	if (j == -1)
		return false;

	// Interpolate on current segment -- get t
	float fSegmentLength = m_distances[j + 1] - m_distances[j];
	float t = (fLength - m_distances[j]) / fSegmentLength;

	// Get the indices of the four points along the control polygon for the current segment
	int iPrev = ((j - 1) + M) % M;
	int iCur = j;
	int iNext = (j + 1) % M;
	int iNextNext = (j + 2) % M;

	// Interpolate to get the point (and upvector)
	p = Interpolate(m_controlPoints[iPrev], m_controlPoints[iCur], m_controlPoints[iNext], m_controlPoints[iNextNext], t);
	if (m_controlUpVectors.size() == m_controlPoints.size())
		up = glm::normalize(Interpolate(m_controlUpVectors[iPrev], m_controlUpVectors[iCur], m_controlUpVectors[iNext], m_controlUpVectors[iNextNext], t));

	return true;
}



// Sample a set of control points using an open Catmull-Rom spline, to produce a set of iNumSamples that are (roughly) equally spaced
void CCatmullRom::UniformlySampleControlPoints(int numSamples)
{
	glm::vec3 p, up;

	// Compute the lengths of each segment along the control polygon, and the total length
	ComputeLengthsAlongControlPoints();
	float fTotalLength = m_distances[m_distances.size() - 1];

	// The spacing will be based on the control polygon
	float fSpacing = fTotalLength / numSamples;

	// Call PointAt to sample the spline, to generate the points
	for (int i = 0; i < numSamples; i++) {
		Sample(i * fSpacing, p, up);
		m_centrelinePoints.push_back(p);
		if (m_controlUpVectors.size() > 0)
			m_centrelineUpVectors.push_back(up);

	}


	// Repeat once more for truly equidistant points
	m_controlPoints = m_centrelinePoints;
	m_controlUpVectors = m_centrelineUpVectors;
	m_centrelinePoints.clear();
	m_centrelineUpVectors.clear();
	m_distances.clear();
	ComputeLengthsAlongControlPoints();
	fTotalLength = m_distances[m_distances.size() - 1];
	fSpacing = fTotalLength / numSamples;
	for (int i = 0; i < numSamples; i++) {
		Sample(i * fSpacing, p, up);
		m_centrelinePoints.push_back(p);
		if (m_controlUpVectors.size() > 0)
			m_centrelineUpVectors.push_back(up);
	}


}

void CCatmullRom::CreateCentreline()
{
	SetControlPoints();
	UniformlySampleControlPoints(2000);
	
	glGenVertexArrays(1, &m_vaoCentreline);
	BufferAttribFunc(m_vaoCentreline);

	CVertexBufferObject CenterlineVBO;
	BufferObjectFunc(CenterlineVBO);

	glm::vec2 texCoord[4] =
	{
		glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f)
	};

	glm::vec3 normal(0.0f, 1.0f, 0.0f);

	for (unsigned int i = 0; i < 1999; i++) 
	{
		//AddtoVBO(CenterlineVBO, m_centrelinePoints[i], texCoord[i % 4], normal);
		CenterlineVBO.AddData(&m_centrelinePoints[i], sizeof(glm::vec3));
		CenterlineVBO.AddData(&texCoord[i % 4], sizeof(glm::vec2));
		CenterlineVBO.AddData(&normal, sizeof(glm::vec3));
	}
	//AddtoVBO(CenterlineVBO, m_centrelinePoints[0], texCoord[0], normal);
	CenterlineVBO.AddData(&m_centrelinePoints[0], sizeof(glm::vec3));
	CenterlineVBO.AddData(&texCoord[0], sizeof(glm::vec2));
	CenterlineVBO.AddData(&normal, sizeof(glm::vec3));

	VAOUploadToGPU(CenterlineVBO);
}


void CCatmullRom::RenderCentreline()
{
	// Bind the VAO m_vaoCentreline and render it
	glBindVertexArray(m_vaoCentreline);
	glDrawArrays(GL_POINTS, 0, m_centrelinePoints.size());
	glDrawArrays(GL_LINE_LOOP, 0, m_centrelinePoints.size());

}

void CCatmullRom::CreateOffsetCurves(float textureRepeat)
{
	glm::vec3 pNext;
	float widthOut = 30.0f;
	float widthCentre = 4.0f;

	//--------------------------------------Left offset for CentreLine---------------------------------------

	glGenVertexArrays(1, &m_vaoLeftOffsetCurveforCentreline);
	BufferAttribFunc(m_vaoLeftOffsetCurveforCentreline);

	CVertexBufferObject lcvbo;
	BufferObjectFunc(lcvbo);

	glm::vec2 lctexCoord[4] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, textureRepeat),
		glm::vec2(1.0, textureRepeat),
	};
	glm::vec3 lcnormal(0.0f, 1.0f, 0.0f);

	for (size_t i = 0; i < m_centrelinePoints.size(); i++)
	{
		if (i != m_centrelinePoints.size() - 1)
		{
			pNext = m_centrelinePoints[i + 1];
		}
		else
		{
			pNext = m_centrelinePoints[0];
		}

		glm::vec3 N = CalculateTNB(pNext, i);

		glm::vec3 left = m_centrelinePoints[i] - (widthCentre / 2) * N;
		m_leftOffsetPointsforCentreline.push_back(left);

		//AddtoVBO(lvbo, m_centrelinePoints[i], ltexCoord[i % 4], lnormal);
		lcvbo.AddData(&m_leftOffsetPointsforCentreline[i], sizeof(glm::vec3));
		lcvbo.AddData(&lctexCoord[i % 4], sizeof(glm::vec2));
		lcvbo.AddData(&lcnormal, sizeof(glm::vec3));
	}
	VAOUploadToGPU(lcvbo);

	//--------------------------------------Right offset for CentreLine---------------------------------------

	glGenVertexArrays(1, &m_vaoRightOffsetCurveforCentreline);
	BufferAttribFunc(m_vaoRightOffsetCurveforCentreline);

	CVertexBufferObject rcvbo;
	BufferObjectFunc(rcvbo);

	glm::vec2 rctexCoord[4] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, textureRepeat),
		glm::vec2(1.0, textureRepeat),
	};
	glm::vec3 rcnormal(0.0f, 1.0f, 0.0f);

	for (size_t i = 0; i < m_centrelinePoints.size(); i++)
	{
		if (i != m_centrelinePoints.size() - 1)
		{
			pNext = m_centrelinePoints[i + 1];
		}
		else
		{
			pNext = m_centrelinePoints[0];
		}

		glm::vec3 N = CalculateTNB(pNext, i);

		glm::vec3 right = m_centrelinePoints[i] + (widthCentre / 2) * N;
		m_rightOffsetPointsforCentreline.push_back(right);

		//AddtoVBO(lvbo, m_centrelinePoints[i], ltexCoord[i % 4], lnormal);
		rcvbo.AddData(&m_rightOffsetPointsforCentreline[i], sizeof(glm::vec3));
		rcvbo.AddData(&rctexCoord[i % 4], sizeof(glm::vec2));
		rcvbo.AddData(&rcnormal, sizeof(glm::vec3));
	}
	VAOUploadToGPU(rcvbo);

	//--------------------------------------Left offset for border---------------------------------------

	glGenVertexArrays(1, &m_vaoLeftOffsetCurveforborder);
	BufferAttribFunc(m_vaoLeftOffsetCurveforborder);

	CVertexBufferObject lbvbo;
	BufferObjectFunc(lbvbo);

	glm::vec2 lbtexCoord[4] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, textureRepeat),
		glm::vec2(1.0, textureRepeat),
	};
	glm::vec3 lbnormal(0.0f, 1.0f, 0.0f);

	for (size_t i = 0; i < m_centrelinePoints.size(); i++)
	{
		if (i != m_centrelinePoints.size() - 1)
		{
			pNext = m_centrelinePoints[i + 1];
		}
		else
		{
			pNext = m_centrelinePoints[0];
		}

		glm::vec3 N = CalculateTNB(pNext, i);

		glm::vec3 left = m_centrelinePoints[i] - (widthOut / 2) * N;
		m_leftOffsetPointsforborder.push_back(left);

		//AddtoVBO(lvbo, m_centrelinePoints[i], ltexCoord[i % 4], lnormal);
		lbvbo.AddData(&m_leftOffsetPointsforborder[i], sizeof(glm::vec3));
		lbvbo.AddData(&lbtexCoord[i % 4], sizeof(glm::vec2));
		lbvbo.AddData(&lbnormal, sizeof(glm::vec3));
	}
	VAOUploadToGPU(lbvbo);

	//--------------------------------------Right offset for border---------------------------------------

	glGenVertexArrays(1, &m_vaoRightOffsetCurveforborder);
	BufferAttribFunc(m_vaoRightOffsetCurveforborder);

	CVertexBufferObject rbvbo;
	BufferObjectFunc(rbvbo);

	glm::vec2 rbtexCoord[4] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, textureRepeat),
		glm::vec2(1.0, textureRepeat),
	};
	glm::vec3 rbnormal(0.0f, 1.0f, 0.0f);

	for (size_t i = 0; i < m_centrelinePoints.size(); i++)
	{
		if (i != m_centrelinePoints.size() - 1)
		{
			pNext = m_centrelinePoints[i + 1];
		}
		else
		{
			pNext = m_centrelinePoints[0];
		}

		glm::vec3 N = CalculateTNB(pNext, i);

		glm::vec3 right = m_centrelinePoints[i] + (widthOut / 2) * N;
		m_rightOffsetPointsforborder.push_back(right);

		//AddtoVBO(lvbo, m_centrelinePoints[i], ltexCoord[i % 4], lnormal);
		rbvbo.AddData(&m_rightOffsetPointsforborder[i], sizeof(glm::vec3));
		rbvbo.AddData(&rbtexCoord[i % 4], sizeof(glm::vec2));
		rbvbo.AddData(&rbnormal, sizeof(glm::vec3));
	}
	VAOUploadToGPU(rbvbo);

	//------------------------------------------------------------Left out offset--------------------------------------

	glGenVertexArrays(1, &m_vaoLeftOffsetCurveforTopBorder);
	BufferAttribFunc(m_vaoLeftOffsetCurveforTopBorder);

	CVertexBufferObject lvbo;
	BufferObjectFunc(lvbo);

	glm::vec2 ltexCoord[4] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, textureRepeat),
		glm::vec2(1.0, textureRepeat),
	};
	glm::vec3 lnormal(0.0f, 1.0f, 0.0f);

	for (size_t i = 0; i < m_centrelinePoints.size(); i++)
	{
		if (i != m_centrelinePoints.size() - 1)
		{
			pNext = m_centrelinePoints[i + 1];
		}
		else
		{
			pNext = m_centrelinePoints[0];
		}

		glm::vec3 N = CalculateTNB(pNext, i);

		glm::vec3 left = m_centrelinePoints[i] - (widthOut / 2) * N;
		m_leftOffsetPointsforTopBorder.push_back(left + glm::vec3(0,5,0));

		//AddtoVBO(lvbo, m_centrelinePoints[i], ltexCoord[i % 4], lnormal);
		lvbo.AddData(&m_leftOffsetPointsforTopBorder[i], sizeof(glm::vec3));
		lvbo.AddData(&ltexCoord[i % 4], sizeof(glm::vec2));
		lvbo.AddData(&lnormal, sizeof(glm::vec3));
	}
	VAOUploadToGPU(lvbo);

	//------------------------------------------------------------Right out offset--------------------------------------

	glGenVertexArrays(1, &m_vaoRightOffsetCurveforTopBorder);
	BufferAttribFunc(m_vaoRightOffsetCurveforTopBorder);

	CVertexBufferObject rvbo;
	BufferObjectFunc(rvbo);

	glm::vec2 rtexCoord[4] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, textureRepeat),
		glm::vec2(1.0, textureRepeat),
	};
	glm::vec3 rnormal(0.0f, 1.0f, 0.0f);

	for (size_t i = 0; i < m_centrelinePoints.size(); i++)
	{
		if (i != m_centrelinePoints.size() - 1)
		{
			pNext = m_centrelinePoints[i + 1];
		}
		else
		{
			pNext = m_centrelinePoints[0];
		}

		glm::vec3 N = CalculateTNB(pNext, i);

		glm::vec3 right = m_centrelinePoints[i] + (widthOut / 2) * N;
		m_rightOffsetPointsforTopBorder.push_back(right + glm::vec3(0, 5, 0));

		//AddtoVBO(lvbo, m_centrelinePoints[i], ltexCoord[i % 4], lnormal);
		rvbo.AddData(&m_rightOffsetPointsforTopBorder[i], sizeof(glm::vec3));
		rvbo.AddData(&rtexCoord[i % 4], sizeof(glm::vec2));
		rvbo.AddData(&rnormal, sizeof(glm::vec3));
	}
	VAOUploadToGPU(rvbo);
}

void CCatmullRom::RenderOffsetCurves()
{
	glBindVertexArray(m_vaoLeftOffsetCurveforCentreline);
	glDrawArrays(GL_POINTS, 0, m_leftOffsetPointsforCentreline.size());
	glDrawArrays(GL_LINE_STRIP, 0, m_leftOffsetPointsforCentreline.size());

	glBindVertexArray(m_vaoRightOffsetCurveforCentreline);
	glDrawArrays(GL_POINTS, 0, m_rightOffsetPointsforCentreline.size());
	glDrawArrays(GL_LINE_STRIP, 0, m_rightOffsetPointsforCentreline.size());

	glBindVertexArray(m_vaoLeftOffsetCurveforborder);
	glDrawArrays(GL_POINTS, 0, m_leftOffsetPointsforborder.size());
	glDrawArrays(GL_LINE_STRIP, 0, m_leftOffsetPointsforborder.size());

	glBindVertexArray(m_vaoRightOffsetCurveforborder);
	glDrawArrays(GL_POINTS, 0, m_rightOffsetPointsforborder.size());
	glDrawArrays(GL_LINE_STRIP, 0, m_rightOffsetPointsforborder.size());

	glBindVertexArray(m_vaoLeftOffsetCurveforTopBorder);
	glDrawArrays(GL_POINTS, 0, m_leftOffsetPointsforTopBorder.size());
	glDrawArrays(GL_LINE_STRIP, 0, m_leftOffsetPointsforTopBorder.size());

	glBindVertexArray(m_vaoRightOffsetCurveforTopBorder);
	glDrawArrays(GL_POINTS, 0, m_rightOffsetPointsforTopBorder.size());
	glDrawArrays(GL_LINE_STRIP, 0, m_rightOffsetPointsforTopBorder.size());
}

void CCatmullRom::CreateTrackRails(string directory, string filename, float textureRepeat)
{
	// Load the texture
	m_textureRails.Load(directory + filename, true);

	TextureLoad(m_textureRails);

	//--------------------------------------------Centrline Track---------------------------------------------------

	glGenVertexArrays(1, &m_vaoTrackforCentreLine);
	BufferAttribFunc(m_vaoTrackforCentreLine);

	CVertexBufferObject pathcvbo;
	BufferObjectFunc(pathcvbo);

	glm::vec2 texCoord[4] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, textureRepeat),
		glm::vec2(textureRepeat, 0.0f),
		glm::vec2(textureRepeat, textureRepeat),

	};
	glm::vec3 normal(0.0f, 1.0f, 0.0f);

	for (size_t i = 0; i < m_centrelinePoints.size(); i++)
	{
		//AddtoVBO(pathvbo, m_leftOffsetPoints[i], texCoord[i % 4], normal);
		//AddtoVBO(pathvbo, m_rightOffsetPoints[i], texCoord[i % 4], normal);

		pathcvbo.AddData(&m_leftOffsetPointsforCentreline[i], sizeof(glm::vec3));
		pathcvbo.AddData(&texCoord[i % 2], sizeof(glm::vec2));
		pathcvbo.AddData(&normal, sizeof(glm::vec3));

		pathcvbo.AddData(&m_rightOffsetPointsforCentreline[i], sizeof(glm::vec3));
		pathcvbo.AddData(&texCoord[(i % 2) + 2], sizeof(glm::vec2));
		pathcvbo.AddData(&normal, sizeof(glm::vec3));
		m_vertexCount += 2;

		if (i == m_centrelinePoints.size() - 1)
		{
			//AddtoVBO(pathvbo, m_leftOffsetPoints[0], texCoord[i % 4], normal);
			//AddtoVBO(pathvbo, m_rightOffsetPoints[0], texCoord[i % 4], normal);
			pathcvbo.AddData(&m_leftOffsetPointsforCentreline[0], sizeof(glm::vec3));
			pathcvbo.AddData(&texCoord[0], sizeof(glm::vec2));
			pathcvbo.AddData(&normal, sizeof(glm::vec3));

			pathcvbo.AddData(&m_rightOffsetPointsforCentreline[0], sizeof(glm::vec3));
			pathcvbo.AddData(&texCoord[0], sizeof(glm::vec2));
			pathcvbo.AddData(&normal, sizeof(glm::vec3));
			m_vertexCount += 2;
		}
	}
	VAOUploadToGPU(pathcvbo);

	//---------------------------------------------------Left Border Track------------------------------------------------

	glGenVertexArrays(1, &m_vaoTrackforLeftBorder);
	BufferAttribFunc(m_vaoTrackforLeftBorder);

	CVertexBufferObject pathlbvbo;
	BufferObjectFunc(pathlbvbo);

	glm::vec2 plbtexCoord[4] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, textureRepeat),
		glm::vec2(textureRepeat, 0.0f),
		glm::vec2(textureRepeat, textureRepeat),

	};
	glm::vec3 plbnormal(0.0f, 1.0f, 0.0f);

	for (size_t i = 0; i < m_centrelinePoints.size(); i++)
	{
		//AddtoVBO(pathvbo, m_leftOffsetPoints[i], texCoord[i % 4], normal);
		//AddtoVBO(pathvbo, m_rightOffsetPoints[i], texCoord[i % 4], normal);

		pathlbvbo.AddData(&m_leftOffsetPointsforborder[i], sizeof(glm::vec3));
		pathlbvbo.AddData(&plbtexCoord[i % 2], sizeof(glm::vec2));
		pathlbvbo.AddData(&plbnormal, sizeof(glm::vec3));

		pathlbvbo.AddData(&m_leftOffsetPointsforTopBorder[i], sizeof(glm::vec3));
		pathlbvbo.AddData(&plbtexCoord[(i % 2) + 2], sizeof(glm::vec2));
		pathlbvbo.AddData(&plbnormal, sizeof(glm::vec3));
		m_vertexCount += 2;

		if (i == m_centrelinePoints.size() - 1)
		{
			//AddtoVBO(pathvbo, m_leftOffsetPoints[0], texCoord[i % 4], normal);
			//AddtoVBO(pathvbo, m_rightOffsetPoints[0], texCoord[i % 4], normal);
			pathlbvbo.AddData(&m_leftOffsetPointsforborder[0], sizeof(glm::vec3));
			pathlbvbo.AddData(&plbtexCoord[0], sizeof(glm::vec2));
			pathlbvbo.AddData(&plbnormal, sizeof(glm::vec3));

			pathlbvbo.AddData(&m_leftOffsetPointsforTopBorder[0], sizeof(glm::vec3));
			pathlbvbo.AddData(&plbtexCoord[0], sizeof(glm::vec2));
			pathlbvbo.AddData(&plbnormal, sizeof(glm::vec3));
			m_vertexCount += 2;
		}
	}
	VAOUploadToGPU(pathlbvbo);

	//------------------------------------Right Border Track----------------------------------------------

	glGenVertexArrays(1, &m_vaoTrackforRightBorder);
	BufferAttribFunc(m_vaoTrackforRightBorder);

	CVertexBufferObject pathrbvbo;
	BufferObjectFunc(pathrbvbo);

	glm::vec2 prbtexCoord[4] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, textureRepeat),
		glm::vec2(textureRepeat, 0.0f),
		glm::vec2(textureRepeat, textureRepeat),

	};
	glm::vec3 prbnormal(0.0f, 1.0f, 0.0f);

	for (size_t i = 0; i < m_centrelinePoints.size(); i++)
	{
		//AddtoVBO(pathvbo, m_leftOffsetPoints[i], texCoord[i % 4], normal);
		//AddtoVBO(pathvbo, m_rightOffsetPoints[i], texCoord[i % 4], normal);

		pathrbvbo.AddData(&m_rightOffsetPointsforborder[i], sizeof(glm::vec3));
		pathrbvbo.AddData(&prbtexCoord[i % 2], sizeof(glm::vec2));
		pathrbvbo.AddData(&prbnormal, sizeof(glm::vec3));

		pathrbvbo.AddData(&m_rightOffsetPointsforTopBorder[i], sizeof(glm::vec3));
		pathrbvbo.AddData(&prbtexCoord[(i % 2) + 2], sizeof(glm::vec2));
		pathrbvbo.AddData(&prbnormal, sizeof(glm::vec3));
		m_vertexCount += 2;

		if (i == m_centrelinePoints.size() - 1)
		{
			//AddtoVBO(pathvbo, m_leftOffsetPoints[0], texCoord[i % 4], normal);
			//AddtoVBO(pathvbo, m_rightOffsetPoints[0], texCoord[i % 4], normal);
			pathrbvbo.AddData(&m_rightOffsetPointsforborder[0], sizeof(glm::vec3));
			pathrbvbo.AddData(&prbtexCoord[0], sizeof(glm::vec2));
			pathrbvbo.AddData(&prbnormal, sizeof(glm::vec3));

			pathrbvbo.AddData(&m_rightOffsetPointsforTopBorder[0], sizeof(glm::vec3));
			pathrbvbo.AddData(&prbtexCoord[0], sizeof(glm::vec2));
			pathrbvbo.AddData(&prbnormal, sizeof(glm::vec3));
			m_vertexCount += 2;
		}
	}
	VAOUploadToGPU(pathrbvbo);
}

void CCatmullRom::RenderTrackRails()
{
	m_textureRails.Bind();

	glBindVertexArray(m_vaoTrackforCentreLine);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_vertexCount);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBindVertexArray(m_vaoTrackforLeftBorder);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_vertexCount);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBindVertexArray(m_vaoTrackforRightBorder);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_vertexCount);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void CCatmullRom::CreateTrackBars(string directory, string filename,float textureRepeat)
{
	// Load the texture
	m_textureBars.Load(directory + filename, true);
	
	TextureLoad(m_textureBars);

	glm::vec2 texCoord[4] =
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, textureRepeat),
		glm::vec2(textureRepeat, 0.0f),
		glm::vec2(textureRepeat, textureRepeat),

	};
	glm::vec3 normal(0.0f, 1.0f, 0.0f);

	//---------------------------------------------------Left Track from centre------------------------------------------------

	m_vertexCount = 0;

	glGenVertexArrays(1, &m_vaoTrackLeft);
	BufferAttribFunc(m_vaoTrackLeft);

	CVertexBufferObject pathlvbo;
	BufferObjectFunc(pathlvbo);

	for (size_t i = 0; i < m_centrelinePoints.size(); i++)
	{
		//AddtoVBO(pathvbo, m_leftOffsetPoints[i], texCoord[i % 4], normal);
		//AddtoVBO(pathvbo, m_rightOffsetPoints[i], texCoord[i % 4], normal);
		pathlvbo.AddData(&m_leftOffsetPointsforborder[i], sizeof(glm::vec3));
		pathlvbo.AddData(&texCoord[i % 2], sizeof(glm::vec2));
		pathlvbo.AddData(&normal, sizeof(glm::vec3));

		pathlvbo.AddData(&m_leftOffsetPointsforCentreline[i], sizeof(glm::vec3));
		pathlvbo.AddData(&texCoord[(i % 2) + 2], sizeof(glm::vec2));
		pathlvbo.AddData(&normal, sizeof(glm::vec3));
		m_vertexCount += 2;
		
		if (i == m_centrelinePoints.size() - 1)
		{
			//AddtoVBO(pathvbo, m_leftOffsetPoints[0], texCoord[i % 4], normal);
			//AddtoVBO(pathvbo, m_rightOffsetPoints[0], texCoord[i % 4], normal);
			pathlvbo.AddData(&m_leftOffsetPointsforborder[0], sizeof(glm::vec3));
			pathlvbo.AddData(&texCoord[0], sizeof(glm::vec2));
			pathlvbo.AddData(&normal, sizeof(glm::vec3));

			pathlvbo.AddData(&m_leftOffsetPointsforCentreline[0], sizeof(glm::vec3));
			pathlvbo.AddData(&texCoord[0], sizeof(glm::vec2));
			pathlvbo.AddData(&normal, sizeof(glm::vec3));
			m_vertexCount += 2;
		}
	}
	VAOUploadToGPU(pathlvbo);

	//------------------------------------Right Track from centre----------------------------------------------

	m_vertexCount = 0;

	glGenVertexArrays(1, &m_vaoTrackRight);
	BufferAttribFunc(m_vaoTrackRight);

	CVertexBufferObject pathrvbo;
	BufferObjectFunc(pathrvbo);

	for (size_t i = 0; i < m_centrelinePoints.size(); i++)
	{
		//AddtoVBO(pathvbo, m_leftOffsetPoints[i], texCoord[i % 4], normal);
		//AddtoVBO(pathvbo, m_rightOffsetPoints[i], texCoord[i % 4], normal);

		pathrvbo.AddData(&m_rightOffsetPointsforborder[i], sizeof(glm::vec3));
		pathrvbo.AddData(&texCoord[i % 2], sizeof(glm::vec2));
		pathrvbo.AddData(&normal, sizeof(glm::vec3));

		pathrvbo.AddData(&m_rightOffsetPointsforCentreline[i], sizeof(glm::vec3));
		pathrvbo.AddData(&texCoord[(i % 2) + 2], sizeof(glm::vec2));
		pathrvbo.AddData(&normal, sizeof(glm::vec3));
		m_vertexCount += 2;
		
		if (i == m_centrelinePoints.size() - 1)
		{
			//AddtoVBO(pathvbo, m_leftOffsetPoints[0], texCoord[i % 4], normal);
			//AddtoVBO(pathvbo, m_rightOffsetPoints[0], texCoord[i % 4], normal);
			pathrvbo.AddData(&m_rightOffsetPointsforborder[0], sizeof(glm::vec3));
			pathrvbo.AddData(&texCoord[0], sizeof(glm::vec2));
			pathrvbo.AddData(&normal, sizeof(glm::vec3));

			pathrvbo.AddData(&m_rightOffsetPointsforCentreline[0], sizeof(glm::vec3));
			pathrvbo.AddData(&texCoord[0], sizeof(glm::vec2));
			pathrvbo.AddData(&normal, sizeof(glm::vec3));
			m_vertexCount += 2;
		}
	}
	VAOUploadToGPU(pathrvbo);
}

void CCatmullRom::RenderTrackBars()
{
	m_textureBars.Bind();

	glBindVertexArray(m_vaoTrackLeft);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_vertexCount);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBindVertexArray(m_vaoTrackRight);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_vertexCount);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

int CCatmullRom::CurrentLap(float d)
{
	return (int)(d / m_distances.back());
}

glm::vec3 CCatmullRom::CalculateTNB(glm::vec3 Next, int element)
{
	glm::vec3 T = glm::normalize(Next - m_centrelinePoints[element]);
	glm::vec3 N = glm::normalize(glm::cross(T, m_centrelineUpVectors[element]));
	glm::vec3 B = glm::normalize(glm::cross(N, T));

	return N;
}
void CCatmullRom::BufferAttribFunc(GLuint VAO)
{
	glBindVertexArray(VAO);
}

void CCatmullRom::BufferObjectFunc(CVertexBufferObject VBO)
{
	VBO.Create();
	VBO.Bind();
}

void CCatmullRom::AddtoVBO(CVertexBufferObject VBO, glm::vec3 points, glm::vec2 texCoord, glm::vec3 normal)
{
	VBO.AddData(&points, sizeof(glm::vec3));
	VBO.AddData(&texCoord, sizeof(glm::vec2));
	VBO.AddData(&normal, sizeof(glm::vec3));
}

void CCatmullRom::VAOUploadToGPU(CVertexBufferObject VBO)
{
	// Upload the VBO to the GPU
	VBO.UploadDataToGPU(GL_STATIC_DRAW);
	// Set the vertex attribute locations
	GLsizei stride = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);
	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)sizeof(glm::vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride,
		(void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
}

glm::vec3 CCatmullRom::_dummy_vector(0.0f, 0.0f, 0.0f);