#pragma once
#include <android/log.h>

#ifndef HOOKLOG_TAG
#define HOOKLOG_TAG "SpaceHooks"
#endif

#define HOOKLOGD(...) __android_log_print(ANDROID_LOG_DEBUG, HOOKLOG_TAG, __VA_ARGS__)
#define HOOKLOGW(...) __android_log_print(ANDROID_LOG_WARN,  HOOKLOG_TAG, __VA_ARGS__)
#define HOOKLOGE(...) __android_log_print(ANDROID_LOG_ERROR, HOOKLOG_TAG, __VA_ARGS__)