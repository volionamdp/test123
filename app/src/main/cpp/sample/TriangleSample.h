//
// Created by ByteFlow on 2019/7/9.
//

#ifndef NDK_OPENGLES_3_0_TRIANGLESAMPLE_H
#define NDK_OPENGLES_3_0_TRIANGLESAMPLE_H

#include "stdint.h"
#include <GLES3/gl3.h>
#include <ImageDef.h>
#include <ByteFlowLock.h>

class TriangleSample
{
public:
	TriangleSample();
	virtual ~TriangleSample();

	virtual void Init();

	virtual void Draw();

	virtual void Destroy();

protected:
	GLuint m_VertexShader;
	GLuint m_FragmentShader;
	GLuint m_ProgramObj;
	int m_SurfaceWidth;
	int m_SurfaceHeight;
};



#endif //NDK_OPENGLES_3_0_TRIANGLESAMPLE_H
