//
// Created by Nam on 24/10/2021.
//

#ifndef TEST1_LOADIMAGESAMPLE_H
#define TEST1_LOADIMAGESAMPLE_H
#include "GLSampleBase.h"
#include "ImageDef.h"
class LoadImageSample : public GLSampleBase{
public:
    LoadImageSample();
    virtual ~LoadImageSample();
    virtual void LoadImage(NativeImage *pImage);
    virtual void Init();
    virtual void Draw(int screenW, int screenH);

    virtual void Destroy();

protected:
    GLuint m_VertexShader;
    GLuint m_FragmentShader;
    GLuint m_ProgramObj;
    GLuint m_MVPMatLoc;
    GLuint m_TextureId;
    GLuint m_SamplerLoc;
    glm::mat4 m_MVPMatrix;
    NativeImage m_RenderImage;
    double startTime;
    float m_X;
    float m_Y;
    int m_SurfaceWidth;
    int m_SurfaceHeight;
};
#endif //TEST1_LOADIMAGESAMPLE_H
