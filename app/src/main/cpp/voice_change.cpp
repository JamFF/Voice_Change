#include <jni.h>
#include <string>
#include <unistd.h>
#include <android/log.h>
#include "com_jamff_voice_EffectUtils.h"
#include "fmod.hpp"

#define LOG_I(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"JamFF",FORMAT,##__VA_ARGS__);
#define LOG_E(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"JamFF",FORMAT,##__VA_ARGS__);

extern "C"
JNIEXPORT void JNICALL
Java_com_jamff_voice_EffectUtils_change(
        JNIEnv *env, jclass jcls, jstring path_jstr, jint type) {

    const char *path_cstr = env->GetStringUTFChars(path_jstr, NULL);
    LOG_I("%s", path_cstr);

    FMOD::System *system;
    FMOD::Sound *sound;
    FMOD::Channel *channel = 0;
    bool playing = true;
    float frequency = 0;

    // digital signal process
    FMOD::DSP *dsp;

    // 初始化
    FMOD::System_Create(&system);

    system->init(32, FMOD_INIT_NORMAL, NULL);

    // 创建声音
    system->createSound(path_cstr, FMOD_DEFAULT, 0, &sound);

    try {
        switch (type) {
            case com_jamff_voice_EffectUtils_MODE_NORMAL:
                LOG_I("%s", "原生");
                system->playSound(sound, 0, false, &channel);
                break;

            case com_jamff_voice_EffectUtils_MODE_LUOLI:
                // 提高声调
                LOG_I("%s", "萝莉");
                // dsp -> 音效 创建fmod中预定义好的音效
                // FMOD_DSP_TYPE_PITCHSHIFT dsp，提升或者降低音调用的一种音效
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                // 设置音调的参数
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2.0);

                system->playSound(sound, 0, false, &channel);
                // 添加到channel
                channel->addDSP(0, dsp);
                break;

            case com_jamff_voice_EffectUtils_MODE_DASHU:
                // 降低声调
                LOG_I("%s", "大叔");
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8);

                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;

            case com_jamff_voice_EffectUtils_MODE_JINGSONG:
                LOG_I("%s", "惊悚");
                // 颤抖
                system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.5);

                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;

            case com_jamff_voice_EffectUtils_MODE_GAOGUAI:
                // 提高说话的速度
                LOG_I("%s", "搞怪");
                system->playSound(sound, 0, false, &channel);
                channel->getFrequency(&frequency);
                frequency = frequency * 1.6f;
                channel->setFrequency(frequency);
                break;

            case com_jamff_voice_EffectUtils_MODE_KONGLING:
                // 回声
                LOG_I("%s", "空灵");
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);// 回音与原生的间隔
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 10);// 回声的次数

                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;

            default:
                break;
        }
    } catch (...) {
        LOG_E("%s", "发生异常")
        // 发生异常跳过后面的逻辑，执行end然后结束程序
        goto end;
    }

    system->update();

    while (playing) {
        channel->isPlaying(&playing);
        // 50毫秒检测一次是否播放结束
        usleep(50 * 1000);// 单位是微秒
    }

    end:
    LOG_E("%s", "start")
    sound->release();
    // 释放资源
    sound->release();
    system->close();
    env->ReleaseStringUTFChars(path_jstr, path_cstr);
    LOG_E("%s", "end")
}