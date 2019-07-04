package com.wentsingnee.minesweeper;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.DialogInterface;
import android.content.res.ColorStateList;
import android.media.AudioManager;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.RequiresApi;
import android.support.v7.widget.Toolbar;
import android.support.v7.app.AppCompatActivity;
import android.util.Pair;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TableLayout;
import android.widget.Button;
import android.widget.TextView;

class ButtonStyleHandlingFactory {
    class ButtonColor {
        public static final int validButton = 0xFF818EDA;
        public static final int invalidButton = 0xFFDDE4F0;
        public static final int mineArea = 0xFFFF8A80;
    }

    public static void setMineButtonStyle(Button btn) {
        btn.setText("\uD83D\uDCA3"); // bomp icon
        int[] colors = {ButtonColor.mineArea};
        int[][] states = {{}};
        btn.setBackgroundTintList(new ColorStateList(states, colors));
    }

    public static void setFlagButtonStyle(Button btn) {
        btn.setText("\uD83C\uDFC1"); // flag icon
    }

    public static void removeFlagButtonStyle(Button btn) {
        btn.setText("");
    }

    @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    static void setInvalidButtonStyle(Button btn, int value) {
        btn.setClickable(false);
        btn.setText(value == 0 ? "" : Integer.toString(value));
        int[] colors = {ButtonColor.invalidButton};
        int[][] states = {{}};
        btn.setBackgroundTintList(new ColorStateList(states, colors));
    }

}

public class MainActivity extends AppCompatActivity {

    SoundEffectManager soundEffectManager;

    void onceRound(int rows, int cols) {
        TableLayout mainLayout = this.findViewById(R.id.mainLayout);
        mainLayout.removeAllViews();
        GameRound gameRound = new GameRound(this, rows, cols);
        gameRound.start();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        this.soundEffectManager = new SoundEffectManager(this);
        this.soundEffectManager.loadSoundRes(R.raw.cheer, 1);
        this.soundEffectManager.loadSoundRes(R.raw.drop, 1);
        this.soundEffectManager.loadSoundRes(R.raw.boom, 1);
        onceRound(15, 10);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        switch (id) {
            case R.id.new_round: {
                final NewRoundSizeDialog newRoundSizeDialog = new NewRoundSizeDialog();
                newRoundSizeDialog.showSingleChoiceDialog(MainActivity.this, new DialogInterface.OnClickListener() {

                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Pair<Integer, Integer> size = newRoundSizeDialog.getChoice();
                        onceRound(size.first, size.second);
                    }
                });

                return true;
            }
        }
        return super.onOptionsItemSelected(item);
    }

    @SuppressLint("SetTextI18n")
    public void updateMineNum(int mine, int marked) {
        TextView mineNumTip = findViewById(R.id.mineNumTip);
        mineNumTip.setText("共有雷 " + mine + " 个, 已标记 " + marked + " 个");
    }

    public void playSound(int sound) {
        // 获取AudioManager引用
        AudioManager am = (AudioManager) this
                .getSystemService(Context.AUDIO_SERVICE);
        // 获取当前音量
        float streamVolumeCurrent = am
                .getStreamVolume(AudioManager.STREAM_MUSIC);
        // 获取系统最大音量
        float streamVolumeMax = am
                .getStreamMaxVolume(AudioManager.STREAM_MUSIC);
        // 计算得到播放音量
        float volume = streamVolumeCurrent / streamVolumeMax;

        this.soundEffectManager.playSound(sound, 0, volume);
    }
}
