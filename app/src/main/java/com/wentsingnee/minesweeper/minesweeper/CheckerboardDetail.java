package com.wentsingnee.minesweeper.minesweeper;

public class CheckerboardDetail {
    public long nativePtr; ///< 用于存储C++层的对象指针

    private CheckerboardDetail(CheckerboardDetail src) {
    }

    public native int get(int x, int y);

    protected void finalize() {cppNativeDestructor();}

    private native void cppNativeDestructor();
}
