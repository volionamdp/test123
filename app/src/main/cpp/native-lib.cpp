#include <jni.h>
#include "MyGLRenderContext.h"
extern "C"
JNIEXPORT void JNICALL
Java_com_example_test1_MyNativeRender_native_1OnInit(JNIEnv *env, jobject thiz) {
    MyGLRenderContext::GetInstance();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_test1_MyNativeRender_native_1OnUnInit(JNIEnv *env, jobject thiz) {
    MyGLRenderContext::DestroyInstance();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_test1_MyNativeRender_native_1SetImageData(JNIEnv *env, jobject thiz, jint format,
                                                           jint width, jint height,
                                                           jbyteArray bytes) {
//    int len = env->GetArrayLength(bytes);
//    uint8_t *buf = new uint8_t [len];
//    env->GetByteArrayRegion(bytes,0,len,reinterpret_cast<jbyte *>(buf));
//    MyGLRenderContext::GetInstance().

}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_test1_MyNativeRender_native_1OnSurfaceCreated(JNIEnv *env, jobject thiz) {
    MyGLRenderContext::GetInstance()->OnSurfaceCreated();

}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_test1_MyNativeRender_native_1OnSurfaceChanged(JNIEnv *env, jobject thiz,
                                                               jint width, jint height) {
    MyGLRenderContext::GetInstance()->OnSurfaceChanged(width,height);

}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_test1_MyNativeRender_native_1OnDrawFrame(JNIEnv *env, jobject thiz) {
    MyGLRenderContext::GetInstance()->OnDrawFrame();

}