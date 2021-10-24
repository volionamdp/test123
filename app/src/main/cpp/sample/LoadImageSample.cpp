//
// Created by Nam on 24/10/2021.
#include "LoadImageSample.h"
#include "../util/GLUtils.h"

LoadImageSample::LoadImageSample() {

}

LoadImageSample::~LoadImageSample() {

}

void LoadImageSample::LoadImage(NativeImage *pImage) {
    m_RenderImage.width = pImage->width;
    m_RenderImage.height = pImage->height;
    m_RenderImage.format = pImage->format;
    NativeImageUtil::CopyNativeImage(pImage, &m_RenderImage);
}

void LoadImageSample::Init() {
    glGenTextures(1,&m_TextureId);
    glBindTexture(GL_TEXTURE_2D,m_TextureId);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,GL_NONE);
    char ver[] = "#version 300 es                           \n"
                 "layout(location = 0) in vec4 vPosition;   \n"
                 "layout(location = 1) in vec2 a_texCoord;   \n"
                 "out vec2 v_texCoord;                      \n"
                 "void main()                              \n"
                 "{                                        \n"
                 " gl_Position = vPosition;                \n"
                 " v_texCoord  = a_texCoord;                 \n"
                 "}";
    char frag[] = "#version 300 es                          \n"
                  "precision mediump float;                 \n"
                  "layout(location = 0) out vec4 fragColor3;                     \n"
                  "in vec2 v_texCoord;                      \n"
                  "uniform sampler2D s_Texture;             \n"
                  "void main()                              \n"
                  "{                                        \n"
                  " fragColor3 =texture(s_Texture, v_texCoord);     \n"
                  "}";
    m_ProgramObj = GLUtils::CreateProgram(ver, frag, m_VertexShader, m_FragmentShader);
    if (m_ProgramObj){
        m_SamplerLoc = glGetUniformLocation(m_ProgramObj,"s_Texture");
    }

}

void LoadImageSample::Draw(int height, int width) {
    GLfloat verticesCoords[] = {
            -1.0f,  0.5f, 0.0f,  // Position 0
            -1.0f, -0.5f, 0.0f,  // Position 1
            1.0f, -0.5f, 0.0f,   // Position 2
            1.0f,  0.5f, 0.0f,   // Position 3
    };

    GLfloat textureCoords[] = {
            0.0f,  0.0f,        // TexCoord 0
            0.0f,  1.0f,        // TexCoord 1
            1.0f,  1.0f,        // TexCoord 2
            1.0f,  0.0f         // TexCoord 3
    };
    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

    if (m_ProgramObj == 0) {
        LOGCATE("loi load program obj");
        return;
    }
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 1.0, 1.0);

    LOGCATE("draw");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,m_TextureId);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,m_RenderImage.width,m_RenderImage.height,0,GL_RGBA,GL_UNSIGNED_BYTE,m_RenderImage.ppPlane[0]);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,GL_NONE);


    glUseProgram(m_ProgramObj);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), verticesCoords);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2* sizeof(GLfloat), textureCoords);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,m_TextureId);
    glUniform1i(m_SamplerLoc,0);


    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT,indices);
}

void LoadImageSample::Destroy() {}

//

