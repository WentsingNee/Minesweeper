package com.wentsingnee.minesweeper;

import android.content.res.ColorStateList;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.support.design.widget.Snackbar;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TableLayout;
import android.widget.TableRow;

import com.wentsingnee.minesweeper.minesweeper.Checkerboard;
import com.wentsingnee.minesweeper.minesweeper.CheckerboardDetail;
import com.wentsingnee.minesweeper.minesweeper.ClickResult;

class GameRound {
    private MainActivity activity;

    private int rows;
    private int cols;
    private Checkerboard checkerboard = null;
    private Button[][] btnArray = null;
    private int setFlagCount;

    public GameRound(MainActivity activity, int rows, int cols) {
        this.activity = activity;
        this.rows = rows;
        this.cols = cols;
        this.setFlagCount = 0;
    }

    private void printCheckboardDetailsToLog(CheckerboardDetail checkerBoardDetail) {
        String s = new String("  \n");
        for (int i = 0; i < this.rows; ++i) {
            for (int j = 0; j < this.cols; ++j) {
                s += Integer.toString(checkerBoardDetail.get(i, j)) + "  ";
            }
            s += "\n";
        }
        Log.i("keymatch", s);
    }

    class EachClick implements View.OnClickListener {
        GameRound gameRound;
        int x;
        int y;

        public EachClick(GameRound gameRound, int x, int y) {
            this.gameRound = gameRound;
            this.x = x;
            this.y = y;
        }

        @Override
        public void onClick(View v) {
            int height = checkerboard.getHeight();
            int width = checkerboard.getWidth();
            ClickResult clickResult = checkerboard.clickOn(this.x, this.y);
            switch (clickResult.clickEventCategory) {
                case click_on_mine: {
                    CheckerboardDetail checkerBoardDetail = checkerboard.getUncoveredCheckerboardDetail();
                    this.gameRound.activity.playSound(R.raw.boom);
                    this.gameRound.refresh(checkerBoardDetail);
                    Snackbar.make(v, "您不幸踩雷", Snackbar.LENGTH_LONG).show();
                    break;
                }
                case click_on_valid_area: {
                    CheckerboardDetail checkerBoardDetail = checkerboard.getCoveredCheckerboardDetail();
                    this.gameRound.activity.playSound(R.raw.drop);
                    this.gameRound.refresh(checkerBoardDetail);
                    break;
                }
                case success: {
                    CheckerboardDetail checkerBoardDetail = checkerboard.getUncoveredCheckerboardDetail();
                    this.gameRound.activity.playSound(R.raw.cheer);
                    this.gameRound.refresh(checkerBoardDetail);
                    Snackbar.make(v, "祝贺", Snackbar.LENGTH_LONG).show();
                    break;
                }
                default: {

                }
            }
            printCheckboardDetailsToLog(checkerboard.getUncoveredCheckerboardDetail());
            printCheckboardDetailsToLog(checkerboard.getCoveredCheckerboardDetail());
        }
    }

    class EachLongClick implements View.OnLongClickListener {

        GameRound gameRound;
        int x;
        int y;

        EachLongClick(GameRound gameRound, int x, int y) {
            this.gameRound = gameRound;
            this.x = x;
            this.y = y;
        }

        @Override
        public boolean onLongClick(View v) {
            int height = checkerboard.getHeight();
            int width = checkerboard.getWidth();
            ClickResult clickResult = checkerboard.setFlag(this.x, this.y);
            switch (clickResult.clickEventCategory) {
                case set_flag: {
                    ++this.gameRound.setFlagCount;
                    CheckerboardDetail checkerBoardDetail = checkerboard.getCoveredCheckerboardDetail();
                    this.gameRound.refresh(checkerBoardDetail);
                    this.gameRound.activity.updateMineNum(this.gameRound.checkerboard.getMineNum(), this.gameRound.setFlagCount);
                    break;
                }
                case remove_flag: {
                    --this.gameRound.setFlagCount;
                    CheckerboardDetail checkerBoardDetail = checkerboard.getCoveredCheckerboardDetail();
                    this.gameRound.refresh(checkerBoardDetail);
                    this.gameRound.activity.updateMineNum(this.gameRound.checkerboard.getMineNum(), this.gameRound.setFlagCount);
                    break;
                }
                default: {

                }
            }
            printCheckboardDetailsToLog(checkerboard.getUncoveredCheckerboardDetail());
            printCheckboardDetailsToLog(checkerboard.getCoveredCheckerboardDetail());
            return false;
        }
    }

    void start() {
        initView();
    }

    @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    private void initView() {
        TableLayout mainLayout = this.activity.findViewById(R.id.mainLayout);

        checkerboard = new Checkerboard(this.rows, this.cols);
        this.btnArray = new Button[this.rows][this.cols];
        for (int i = 0; i < this.rows; ++i) {
            TableRow tableRow = new TableRow(this.activity);
            mainLayout.addView(tableRow);

            TableLayout.LayoutParams p =
                    new TableLayout.LayoutParams(TableLayout.LayoutParams.MATCH_PARENT, TableLayout.LayoutParams.MATCH_PARENT, 1);
            tableRow.setLayoutParams(p);

            for (int j = 0; j < this.cols; ++j) {
                this.btnArray[i][j] = new Button(this.activity);
                int id = 2000 + i * this.cols + j;
                {
                    int[] colors = {ButtonStyleHandlingFactory.ButtonColor.validButton};
                    int[][] states = {{}};
                    this.btnArray[i][j].setBackgroundTintList(new ColorStateList(states, colors));
                }
                this.btnArray[i][j].setId(id);
                this.btnArray[i][j].setText("");
//                this.btnArray[i][j].setAutoSizeTextTypeWithDefaults(Button.AUTO_SIZE_TEXT_TYPE_UNIFORM);
                this.btnArray[i][j].setOnClickListener(new EachClick(this, i, j));
                this.btnArray[i][j].setOnLongClickListener(new EachLongClick(this, i, j));
                TableRow.LayoutParams p2 = new TableRow.LayoutParams(TableRow.LayoutParams.MATCH_PARENT, TableRow.LayoutParams.MATCH_PARENT, 1);
                p2.setMargins(0, 0, 0, 0);
                this.btnArray[i][j].setLayoutParams(p2);
                tableRow.addView(this.btnArray[i][j]);
            }
        }
        this.activity.updateMineNum(this.checkerboard.getMineNum(), 0);
    }

    private void refresh(CheckerboardDetail checkerBoardDetail) {
        for (int i = 0; i < this.rows; ++i) {
            for (int j = 0; j < this.cols; ++j) {
                int value = checkerBoardDetail.get(i, j);
                switch (value) {
                    case Checkerboard.FLAG: {
                        ButtonStyleHandlingFactory.setFlagButtonStyle(this.btnArray[i][j]);
                        break;
                    }
                    case Checkerboard.MINE: {
                        ButtonStyleHandlingFactory.setMineButtonStyle(this.btnArray[i][j]);
                        break;
                    }
                    case Checkerboard.INIT: {
                        this.btnArray[i][j].setText("");
                        break;
                    }
                    case 0:
                    default: {
                        ButtonStyleHandlingFactory.setInvalidButtonStyle(this.btnArray[i][j], value);
                    }
                }
            }
        }
    }
}
