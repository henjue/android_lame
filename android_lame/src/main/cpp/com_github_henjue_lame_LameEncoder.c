#include <jni.h>
#include <android/log.h>
#define TAG "android_lame" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型
#include "lame-3.100_libmp3lame/lame.h"

static lame_global_flags *glf = NULL;

JNIEXPORT void JNICALL
Java_com_github_henjue_lame_LameEncoder_init(
        JNIEnv *env, jclass cls, jint inSamplerate, jint outChannel,
        jint outSamplerate, jint outBitrate, jint quality) {
    if (glf != NULL) {
        lame_close(glf);
        glf = NULL;
    }
    glf = lame_init();
    lame_set_in_samplerate(glf, inSamplerate);
    lame_set_num_channels(glf, outChannel);
    lame_set_out_samplerate(glf, outSamplerate);
    lame_set_brate(glf, outBitrate);
    lame_set_quality(glf, quality);
    lame_init_params(glf);

}
JNIEXPORT jstring JNICALL
Java_com_github_henjue_lame_LameEncoder_getVersion(
                JNIEnv* env, jclass cls)
{
    LOGD("version:%s",get_lame_version());
    jstring s=(*env)->NewStringUTF(env,get_lame_version());
    return s;
}


JNIEXPORT jobject JNICALL
Java_com_github_henjue_lame_LameEncoder_getVersionNumerical(
        JNIEnv* env, jclass cls)
{
    lame_version_t v;
    get_lame_version_numerical(&v);
    jclass objectClass = (*env)->FindClass(env,"com/github/henjue/lame/LameVersion");
    jfieldID major = (*env)->GetFieldID(env,objectClass,"major", "I");
    jfieldID minor = (*env)->GetFieldID(env,objectClass,"minor", "I");
    jfieldID alpha = (*env)->GetFieldID(env,objectClass,"alpha", "Z");
    jfieldID beta = (*env)->GetFieldID(env,objectClass,"beta", "Z");
    jfieldID psy_major = (*env)->GetFieldID(env,objectClass,"psy_major", "I");
    jfieldID psy_minor = (*env)->GetFieldID(env,objectClass,"psy_minor", "I");
    jfieldID psy_alpha = (*env)->GetFieldID(env,objectClass,"psy_alpha", "Z");
    jfieldID psy_beta = (*env)->GetFieldID(env,objectClass,"psy_beta", "Z");
    jfieldID features = (*env)->GetFieldID(env,objectClass,"features", "Ljava/lang/String;");

    jmethodID initMethod=(*env)->GetMethodID(env,objectClass,"<init>", "()V");
    jobject obj=(*env)->NewObject(env,objectClass,initMethod);
    (*env)->SetIntField(env,obj,major,v.major);
    (*env)->SetIntField(env,obj,minor,v.minor);
    (*env)->SetBooleanField(env,obj,alpha,v.alpha);
    (*env)->SetBooleanField(env,obj,beta,v.beta);
    (*env)->SetIntField(env,obj,psy_major,v.psy_major);
    (*env)->SetIntField(env,obj,psy_minor,v.psy_minor);
    (*env)->SetBooleanField(env,obj,psy_alpha,v.psy_alpha);
    (*env)->SetBooleanField(env,obj,psy_beta,v.psy_beta);
    (*env)->SetObjectField(env,obj,features,(*env)->NewStringUTF(env,v.features));

    return obj;
}

JNIEXPORT jint JNICALL
Java_com_github_henjue_lame_LameEncoder_encode(
        JNIEnv *env, jclass cls, jshortArray buffer_l, jshortArray buffer_r,
        jint samples, jbyteArray mp3buf) {
    jshort *j_buffer_l = (*env)->GetShortArrayElements(env, buffer_l, NULL);

    jshort *j_buffer_r = (*env)->GetShortArrayElements(env, buffer_r, NULL);

    const jsize mp3buf_size = (*env)->GetArrayLength(env, mp3buf);
    jbyte *j_mp3buf = (*env)->GetByteArrayElements(env, mp3buf, NULL);

    int result = lame_encode_buffer(glf, j_buffer_l, j_buffer_r,
                                    samples, j_mp3buf, mp3buf_size);

    (*env)->ReleaseShortArrayElements(env, buffer_l, j_buffer_l, 0);
    (*env)->ReleaseShortArrayElements(env, buffer_r, j_buffer_r, 0);
    (*env)->ReleaseByteArrayElements(env, mp3buf, j_mp3buf, 0);

    return result;
}

JNIEXPORT jint JNICALL
Java_com_github_henjue_lame_LameEncoder_flush(
        JNIEnv *env, jclass cls, jbyteArray mp3buf) {
    const jsize mp3buf_size = (*env)->GetArrayLength(env, mp3buf);
    jbyte *j_mp3buf = (*env)->GetByteArrayElements(env, mp3buf, NULL);

    int result = lame_encode_flush(glf, j_mp3buf, mp3buf_size);

    (*env)->ReleaseByteArrayElements(env, mp3buf, j_mp3buf, 0);

    return result;
}

JNIEXPORT void JNICALL
Java_com_github_henjue_lame_LameEncoder_close(
        JNIEnv *env, jclass cls) {
    lame_close(glf);
    glf = NULL;
}
