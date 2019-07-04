//
// Created by peter on 19-5-21.
//

#ifndef MINESWEEPER_CLICKRESULTJNI_HPP
#define MINESWEEPER_CLICKRESULTJNI_HPP

#include "minesweeper/ClickResult.hpp"

#include <jni.h>

constexpr const char CLICK_RESULT_CLASS_NAME[] = "com.wentsingnee.minesweeper.minesweeper.ClickResult";
constexpr const char CLICK_EVENT_CATEGORY_SIG[] = "Lcom/wentsingnee/minesweeper/minesweeper/ClickResult$ClickEventCategory;";

jobject
getClickResultCategoryEnumValueField(
        JNIEnv *env,
        minesweeper::ClickResult::ClickEventCategory click_event_category);

void setClickResultValue(JNIEnv *env, jobject & src, int x, int y, minesweeper::ClickResult::ClickEventCategory clickEventCategory);


#endif //MINESWEEPER_CLICKRESULTJNI_HPP
