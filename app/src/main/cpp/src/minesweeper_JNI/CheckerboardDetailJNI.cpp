//
// Created by peter on 19-5-21.
//

#include "minesweeper_JNI/CheckerboardDetailJNI.hpp"

minesweeper::Checkerboard::checker_board_type *getCheckerboardDetail(JNIEnv *env, jobject thiz)
{
    jclass clazz = env->GetObjectClass(thiz);
    jfieldID fid = env->GetFieldID(clazz, "nativePtr", "J");
    jlong ptr = env->GetLongField(thiz, fid);
    return (minesweeper::Checkerboard::checker_board_type *)(ptr);
}

void setCheckerboardDetail(JNIEnv *env, jobject thiz, const minesweeper::Checkerboard::checker_board_type *ptr)
{
    jclass clazz = env->GetObjectClass(thiz);
    jfieldID fid = env->GetFieldID(clazz, "nativePtr", "J");
    env->SetLongField(thiz, fid, (jlong)(ptr));
}

#ifdef __cplusplus
extern "C" {
#endif

jint Java_com_wentsingnee_minesweeper_minesweeper_CheckerboardDetail_get(
        JNIEnv *env,
        jobject thiz,
        jint x, jint y)
{
    const minesweeper::Checkerboard::checker_board_type *p = getCheckerboardDetail(env, thiz);
    return (*p)[x][y];
}

void Java_com_wentsingnee_minesweeper_minesweeper_CheckerboardDetail_cppNativeDestructor(
        JNIEnv *env,
        jobject thiz)
{
    delete getCheckerboardDetail(env, thiz);
}

#ifdef __cplusplus
}
#endif
