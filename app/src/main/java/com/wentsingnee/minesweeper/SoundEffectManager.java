package com.wentsingnee.minesweeper;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.media.AudioManager;

import java.util.HashMap;

class SoundEffectManager {

    private Activity activity;
    private android.media.SoundPool soundPool; ///< 声明SoundPool的引用
    private HashMap<Integer, Integer> soundIDMap; ///< 声明一个HashMap来存放声音文件
    private int currStreamId;///< 当前正播放的streamId

    /**
     * 初始化声音池
     */
    @SuppressLint("UseSparseArrays")
    public SoundEffectManager(Activity activity) {
        this.activity = activity;
        this.soundPool = new android.media.SoundPool(4, AudioManager.STREAM_MUSIC, 0); // 创建SoundPool对象
        this.soundIDMap = new HashMap<Integer, Integer>(); // 创建HashMap对象
    }

    public void loadSoundRes(int sound, int priority)
    {
        this.soundIDMap.put(sound, this.soundPool.load(this.activity, sound, priority));
    }

    /**
     * 播放声音
     */
    public void playSound(int sound, int loop, float volume) {
        if (this.soundIDMap.containsKey(sound) == false) {
            this.loadSoundRes(sound,1);
        }
        currStreamId = this.soundPool.play(this.soundIDMap.get(sound), volume, volume, 1, loop, 1.0f);
    }
}
