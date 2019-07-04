package com.wentsingnee.minesweeper.minesweeper;

public class ClickResult {
    static {
        System.loadLibrary("minesweeper");
    }

    public enum ClickEventCategory {
        click_on_disable_area,
        click_on_valid_area,
        click_on_out_of_range_area,
        click_on_mine,
        set_flag,
        remove_flag,
        success,
    }

    public int x;
    public int y;
    public ClickEventCategory clickEventCategory;
}
