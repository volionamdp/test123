//
// Created by ByteFlow on 2019/7/9.
//

#ifndef NDK_OPENGLES_3_0_TRIANGLESAMPLE_H
#define NDK_OPENGLES_3_0_TRIANGLESAMPLE_H

#include "stdint.h"
#include "GLSampleBase.h"
#include <GLES3/gl3.h>
#include <ImageDef.h>
#include <ByteFlowLock.h>
#include <glm.hpp>

class TriangleSample: public GLSampleBase
{
public:
	TriangleSample();
	virtual ~TriangleSample();

	virtual void Init();

	virtual void setXY(float x,float y);

	virtual void UpdateMatrix(glm::mat4 &mvpMatrix,float x,float y,float ratio);

	virtual void Draw(int screenW, int screenH);

	virtual void Destroy();

	double getTime();

protected:
	GLuint m_VertexShader;
	GLuint m_FragmentShader;
	GLuint m_ProgramObj;
	GLuint m_MVPMatLoc;
	glm::mat4 m_MVPMatrix;
	double startTime;
	float m_X;
	float m_Y;
	int m_SurfaceWidth;
	int m_SurfaceHeight;
};



#endif //NDK_OPENGLES_3_0_TRIANGLESAMPLE_H
