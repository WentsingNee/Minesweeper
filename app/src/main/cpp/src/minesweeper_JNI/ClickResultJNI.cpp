//
// Created by peter on 19-5-21.
//

#include "minesweeper_JNI/ClickResultJNI.hpp"

#include "Log.hpp"

namespace
{
    minesweeper::ClickResult *getClickResult(JNIEnv *env, jobject thiz)
    {
        jclass clazz = env->GetObjectClass(thiz);
        jfieldID fid = env->GetFieldID(clazz, "nativePtr", "J");
        jlong ptr = env->GetLongField(thiz, fid);
        return (minesweeper::ClickResult *)(ptr);
    }

    void setClickResult(JNIEnv *env, jobject thiz, const minesweeper::ClickResult *ptr)
    {
        jclass clazz = env->GetObjectClass(thiz);
        jfieldID fid = env->GetFieldID(clazz, "nativePtr", "J");
        env->SetLongField(thiz, fid, (jlong)(ptr));
    }
}

jobject
getClickResultCategoryEnumValueField(
        JNIEnv *env,
        minesweeper::ClickResult::ClickEventCategory click_event_category)
{
    jclass clrParity = env->FindClass("com.wentsingnee.minesweeper.minesweeper.ClickResult$ClickEventCategory");
    jfieldID  id = nullptr;
    switch (click_event_category) {
        case minesweeper::ClickResult::ClickEventCategory::click_on_disable_area:
            id = env->GetStaticFieldID(clrParity, "click_on_disable_area", CLICK_EVENT_CATEGORY_SIG);
            break;
        case minesweeper::ClickResult::ClickEventCategory::click_on_valid_area:
            id = env->GetStaticFieldID(clrParity, "click_on_valid_area", CLICK_EVENT_CATEGORY_SIG);
            break;
        case minesweeper::ClickResult::ClickEventCategory::click_on_out_of_range_area:
            id = env->GetStaticFieldID(clrParity, "click_on_out_of_range_area", CLICK_EVENT_CATEGORY_SIG);
            break;
        case minesweeper::ClickResult::ClickEventCategory::click_on_mine:
            id = env->GetStaticFieldID(clrParity, "click_on_mine", CLICK_EVENT_CATEGORY_SIG);
            break;
        case minesweeper::ClickResult::ClickEventCategory::set_flag:
            id = env->GetStaticFieldID(clrParity, "set_flag", CLICK_EVENT_CATEGORY_SIG);
            break;
        case minesweeper::ClickResult::ClickEventCategory::remove_flag:
            id = env->GetStaticFieldID(clrParity, "remove_flag", CLICK_EVENT_CATEGORY_SIG);
            break;
        case minesweeper::ClickResult::ClickEventCategory::success:
            id = env->GetStaticFieldID(clrParity, "success", CLICK_EVENT_CATEGORY_SIG);
            break;
    }
    return env->GetStaticObjectField(clrParity, id);
}

void setClickResultValue(JNIEnv *env, jobject & clickResultObj, int x, int y, minesweeper::ClickResult::ClickEventCategory clickEventCategory)
{
    jclass clickResultClz = env->FindClass(CLICK_RESULT_CLASS_NAME);
    jfieldID fid = nullptr;

    fid = env->GetFieldID(clickResultClz, "x", "I");
    env->SetIntField(clickResultObj, fid, x);

    fid = env->GetFieldID(clickResultClz, "y", "I");
    env->SetIntField(clickResultObj, fid, y);

    fid = env->GetFieldID(clickResultClz, "clickEventCategory", CLICK_EVENT_CATEGORY_SIG);
    env->SetObjectField(clickResultObj, fid, getClickResultCategoryEnumValueField(env, clickEventCategory));
}
