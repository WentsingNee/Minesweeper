//
// Created by peter on 19-5-21.
//

#ifndef MINESWEEPER_CHECKERBOARDDETAILJNI_HPP
#define MINESWEEPER_CHECKERBOARDDETAILJNI_HPP

#include <jni.h>
#include "minesweeper/Checkerboard.hpp"

minesweeper::Checkerboard::checker_board_type *getCheckerboardDetail(JNIEnv *env, jobject thiz);
void setCheckerboardDetail(JNIEnv *env, jobject thiz, const minesweeper::Checkerboard::checker_board_type *ptr);


extern "C" JNIEXPORT
        jint JNICALL
Java_com_wentsingnee_minesweeper_minesweeper_CheckerboardDetail_get(
        JNIEnv *env,
        jobject thiz,
        jint x, jint y);

extern "C" JNIEXPORT
void JNICALL
Java_com_wentsingnee_minesweeper_minesweeper_CheckerboardDetail_cppNativeDestructor(
        JNIEnv *env,
jobject thiz);


#endif //MINESWEEPER_CHECKERBOARDDETAILJNI_HPP
