package com.wentsingnee.minesweeper;

import android.app.Activity;
import android.content.DialogInterface;
import android.support.v7.app.AlertDialog;
import android.util.Pair;

public class NewRoundSizeDialog {

    Pair<Integer, Integer> choice = null;

    public Pair<Integer, Integer> getChoice() {
        return this.choice;
    }

    public void showSingleChoiceDialog(Activity parentActivity, DialogInterface.OnClickListener event) {
        final Pair<Integer, Integer>[] items = new Pair[4];
        {
            items[0] = new Pair<>(10, 10);
            items[1] = new Pair<>(12, 12);
            items[2] = new Pair<>(15, 10);
            items[3] = new Pair<>(15, 15);
        }

        String[] itemStrS = new String[4];
        {
            for (int i = 0; i < itemStrS.length; ++i) {
                itemStrS[i] = items[i].first + " * " + items[i].second;
            }
        }

        choice = items[0];

        AlertDialog.Builder singleChoiceDialog = new AlertDialog.Builder(parentActivity);
        singleChoiceDialog.setTitle("请选择新棋盘大小");
        // 第二个参数是默认选项，此处设置为0

        singleChoiceDialog.setSingleChoiceItems(itemStrS, 0,
                new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        choice = items[which];
                    }
                });
        singleChoiceDialog.setPositiveButton("确定", event);
        singleChoiceDialog.show();
    }
}
