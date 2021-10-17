//
// Created by ByteFlow on 2019/7/9.
//

#include <ext.hpp>
#include <gtc/matrix_transform.hpp>
#include "TriangleSample.h"
#include "../util/GLUtils.h"
#include "../util/LogUtil.h"
#include <time.h>


TriangleSample::TriangleSample()
{
	startTime = getTime();
}

TriangleSample::~TriangleSample()
{
}
double TriangleSample::getTime(){
	struct timespec res{};
	clock_gettime(CLOCK_REALTIME, &res);
	return (1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6)/5;
}

void TriangleSample::UpdateMatrix(glm::mat4 &mvpMatrix, float x, float y, float ratio) {
	//glm::mat4 Projection = glm::perspective(45.0f,ratio,0.1f,100.0f);//phép chiếu góc nhìn 45 độ tỉ lệ khung nhìn ratio
	glm::mat4 Projection = glm::ortho(-1.0f,1.0f,-1/ratio,1/ratio,0.1f,100.0f);//phép chiếu góc nhìn 45 độ tỉ lệ khung nhìn ratio

	glm::mat4 View = glm::lookAt(
			glm::vec3(0,0,4), //vị trí camera
			glm::vec3(0,0,0),//vị trí nhìn
			glm::vec3(0,1,0)
			);
	int a = (int)(getTime() - startTime)%360;
	float rotate = MATH_PI/180.0f*a;
	glm::mat4 Model = glm::mat4 (2.0f);
	LOGCATE("zzvv %f  %f",x,y);
	Model = glm::translate(Model,glm::vec3(x,y,0.0f));
	Model = glm::rotate(Model,rotate,glm::vec3(0,1,0));
	mvpMatrix = Projection*View*Model;
}

void TriangleSample::setXY(float x, float y) {
	m_Y = y;
	m_X = x;
}

void TriangleSample::Init()
{
	if(m_ProgramObj != 0)
		return;
	char vShaderStr[] =
			"#version 300 es                          \n"
			"layout(location = 0) in vec4 vPosition;  \n"
			"uniform mat4 u_MVPMatrix;  \n"
			"void main()                              \n"
			"{                                        \n"
			"   gl_Position = u_MVPMatrix*vPosition;              \n"
			"}                                        \n";

	char fShaderStr[] =
			"#version 300 es                              \n"
			"precision mediump float;                     \n"
			"out vec4 fragColor2;                          \n"
			"void main()                                  \n"
			"{                                            \n"
			"   fragColor2 = vec4 ( 1.0, 0.0, 0.5, 1.0 );  \n"
			"}                                            \n";

	m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);
	if (m_ProgramObj){
		m_MVPMatLoc = glGetUniformLocation(m_ProgramObj,"u_MVPMatrix");
	}
}

void TriangleSample::Draw()
{
	LOGCATE("TriangleSample::Draw");
	GLfloat vVertices[] = {
			0.0f,  0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
	};

	if(m_ProgramObj == 0){
		LOGCATE("TriangleSample::Draw m_program 0");
		return;
	}
	UpdateMatrix(m_MVPMatrix,m_X,m_Y,0.5f);

	glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 1.0, 1.0);

	// Use the program object
	glUseProgram (m_ProgramObj);
	glUniformMatrix4fv(m_MVPMatLoc,1,GL_FALSE,&m_MVPMatrix[0][0]);

	// Load the vertex data
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
	glEnableVertexAttribArray (0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glUseProgram (GL_NONE);
	LOGCATE("TriangleSample::Draw ok");


}

void TriangleSample::Destroy()
{
	if (m_ProgramObj)
	{
		glDeleteProgram(m_ProgramObj);
		m_ProgramObj = GL_NONE;
	}

}
