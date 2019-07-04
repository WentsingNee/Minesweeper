//
// Created by peter on 19-5-21.
//

#ifndef MINESWEEPER_CHECKERBOARDJNI_HPP
#define MINESWEEPER_CHECKERBOARDJNI_HPP

#include <jni.h>

extern "C" JNIEXPORT void JNICALL
Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_cppNativeConstructorWithHW(
        JNIEnv *env,
        jobject thiz,
        jint height, jint width);

extern "C" JNIEXPORT void JNICALL
Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_cppNativeConstructorWithHWN(
        JNIEnv *env,
        jobject thiz,
        jint height, jint width, jint mine_num);

extern "C" JNIEXPORT void JNICALL
Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_cppNativeDestructor(
        JNIEnv *env,
        jobject thiz);

extern "C" JNIEXPORT jint JNICALL
        Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_getHeight(
        JNIEnv *env,
        jobject thiz);

extern "C" JNIEXPORT jint JNICALL
        Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_getWidth(
        JNIEnv *env,
        jobject thiz);

extern "C" JNIEXPORT jint JNICALL
Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_getMineNum(
        JNIEnv *env,
        jobject thiz);


extern "C" JNIEXPORT jobject JNICALL
        Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_getUncoveredCheckerboardDetail(
        JNIEnv *env,
        jobject thiz);

extern "C" JNIEXPORT jobject JNICALL
        Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_getCoveredCheckerboardDetail(
        JNIEnv *env,
        jobject thiz);

extern "C" JNIEXPORT jobject JNICALL
Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_clickOn(
        JNIEnv *env,
        jobject thiz,
        jint x, jint y);

extern "C" JNIEXPORT jobject JNICALL
Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_setFlag(
        JNIEnv *env,
        jobject thiz,
        jint x, jint y);

#endif //MINESWEEPER_CHECKERBOARDJNI_HPP
