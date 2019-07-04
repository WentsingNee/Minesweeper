package com.wentsingnee.minesweeper.minesweeper;

public class Checkerboard {
    static {
        System.loadLibrary("minesweeper");
    }

    public static final int INIT = -1;
    public static final int MINE = -2;
    public static final int FLAG = -3;

    private long nativePtr; ///< 用于存储C++层的对象指针

    public Checkerboard(int height, int width) {
        cppNativeConstructorWithHW(height, width);
    }

    public Checkerboard(int height, int width, int mine_num) {
        cppNativeConstructorWithHWN(height, width, mine_num);
    }

    private Checkerboard(Checkerboard src) {
    }

    protected void finalize() {
        cppNativeDestructor();
    }

    private native void cppNativeConstructorWithHW(int height, int width);

    private native void cppNativeConstructorWithHWN(int height, int width, int mine_num);

    private native void cppNativeDestructor();

    public native int getHeight();

    public native int getWidth();

    public native int getMineNum();

    public native CheckerboardDetail getUncoveredCheckerboardDetail();

    public native CheckerboardDetail getCoveredCheckerboardDetail();

    public native ClickResult clickOn(int x, int y);

    public native ClickResult setFlag(int x, int y);
}
