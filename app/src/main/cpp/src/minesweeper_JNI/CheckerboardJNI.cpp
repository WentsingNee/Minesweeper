//
// Created by peter on 19-5-21.
//

#include "minesweeper_JNI/CheckerboardDetailJNI.hpp"
#include "minesweeper_JNI/CheckerboardJNI.hpp"
#include "minesweeper_JNI/ClickResultJNI.hpp"

#include "Log.hpp"

namespace
{
    minesweeper::Checkerboard *getCheckerboard(JNIEnv *env, jobject thiz)
    {
        jclass clazz = env->GetObjectClass(thiz);
        jfieldID fid = env->GetFieldID(clazz, "nativePtr", "J");
        jlong ptr = env->GetLongField(thiz, fid);
        return (minesweeper::Checkerboard *)(ptr);
    }

    void setCheckerboard(JNIEnv *env, jobject thiz, const minesweeper::Checkerboard *ptr)
    {
        jclass clazz = env->GetObjectClass(thiz);
        jfieldID fid = env->GetFieldID(clazz, "nativePtr", "J");
        env->SetLongField(thiz, fid, (jlong)(ptr));
    }
}


#ifdef __cplusplus
extern "C" {
#endif


void Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_cppNativeConstructorWithHW(
        JNIEnv *env,
        jobject thiz,
        jint height, jint width)
{
    minesweeper::Checkerboard *ptr = new minesweeper::Checkerboard(height, width);
    setCheckerboard(env, thiz, ptr);
}

void Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_cppNativeConstructorWithHWN(
        JNIEnv *env,
        jobject thiz,
        jint height, jint width, jint mine_num)
{
    minesweeper::Checkerboard *ptr = new minesweeper::Checkerboard(height, width, mine_num);
    setCheckerboard(env, thiz, ptr);
}

void Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_cppNativeDestructor(
        JNIEnv *env,
        jobject thiz)
{
    delete getCheckerboard(env, thiz);
}

jint Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_getHeight(
        JNIEnv *env,
        jobject thiz)
{
    minesweeper::Checkerboard *p = getCheckerboard(env, thiz);
    return p->get_height();
}

jint Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_getWidth(
        JNIEnv *env,
        jobject thiz)
{
    const minesweeper::Checkerboard *p = getCheckerboard(env, thiz);
    return p->get_width();
}

jint Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_getMineNum(
        JNIEnv *env,
        jobject thiz)
{
    const minesweeper::Checkerboard *p = getCheckerboard(env, thiz);
    return p->get_mine_num();
}

jobject Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_getUncoveredCheckerboardDetail(
        JNIEnv *env,
        jobject thiz)
{
    minesweeper::Checkerboard *p = getCheckerboard(env, thiz);

    minesweeper::Checkerboard::checker_board_type checkerBoardDetail =
            p->get_uncovered_checkerboard_detail();

    jobject checkboardDetailObj = nullptr;
    {
        jclass checkboardDetailClz = env->FindClass("com.wentsingnee.minesweeper.minesweeper.CheckerboardDetail");
        jmethodID initMID = env->GetMethodID(checkboardDetailClz, "<init>", "()V");
        checkboardDetailObj = env->NewObject(checkboardDetailClz, initMID);
    }
    minesweeper::Checkerboard::checker_board_type * detailPtr = new minesweeper::Checkerboard::checker_board_type(checkerBoardDetail);
    setCheckerboardDetail(env, checkboardDetailObj, detailPtr);
    return checkboardDetailObj;
}

jobject Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_getCoveredCheckerboardDetail(
        JNIEnv *env,
        jobject thiz)
{
    minesweeper::Checkerboard *p = getCheckerboard(env, thiz);

    minesweeper::Checkerboard::checker_board_type checkerBoardDetail =
            p->get_covered_checkerboard_detail();

    jobject checkboardDetailObj = nullptr;
    {
        jclass checkboardDetailClz = env->FindClass("com.wentsingnee.minesweeper.minesweeper.CheckerboardDetail");
        jmethodID initMID = env->GetMethodID(checkboardDetailClz, "<init>", "()V");
        checkboardDetailObj = env->NewObject(checkboardDetailClz, initMID);
    }
    minesweeper::Checkerboard::checker_board_type * detailPtr = new minesweeper::Checkerboard::checker_board_type(checkerBoardDetail);
    setCheckerboardDetail(env, checkboardDetailObj, detailPtr);
    return checkboardDetailObj;
}

jobject Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_clickOn(
        JNIEnv *env,
        jobject thiz,
        jint x, jint y)
{
    minesweeper::Checkerboard *ptr_to_checkerboard = getCheckerboard(env, thiz);
    minesweeper::ClickResult clickResult = ptr_to_checkerboard->click_on(x, y);

    jobject clickResultObj = nullptr;
    {
        jclass clickResultClz = env->FindClass(CLICK_RESULT_CLASS_NAME);
        jmethodID initMID = env->GetMethodID(clickResultClz, "<init>", "()V");
        clickResultObj = env->NewObject(clickResultClz, initMID);
        setClickResultValue(env, clickResultObj, clickResult.x, clickResult.y, clickResult.click_event_category);
    }
    return clickResultObj;
}

jobject Java_com_wentsingnee_minesweeper_minesweeper_Checkerboard_setFlag(
        JNIEnv *env,
        jobject thiz,
        jint x, jint y)
{
    minesweeper::Checkerboard *ptr_to_checkerboard = getCheckerboard(env, thiz);
    minesweeper::ClickResult clickResult = ptr_to_checkerboard->set_flag(x, y);

    jobject clickResultObj = nullptr;
    {
        jclass clickResultClz = env->FindClass(CLICK_RESULT_CLASS_NAME);
        jmethodID initMID = env->GetMethodID(clickResultClz, "<init>", "()V");
        clickResultObj = env->NewObject(clickResultClz, initMID);
        setClickResultValue(env, clickResultObj, clickResult.x, clickResult.y, clickResult.click_event_category);
    }
    return clickResultObj;
}

#ifdef __cplusplus
} // end of extern "C"
#endif