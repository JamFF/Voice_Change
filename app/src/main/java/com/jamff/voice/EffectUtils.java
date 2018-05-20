package com.jamff.voice;

/**
 * 描述：
 * 作者：JamFF
 * 创建时间：2018/5/20 12:26
 */
public class EffectUtils {

    // 音效的类型
    public static final int MODE_NORMAL = 0;
    public static final int MODE_LUOLI = 1;
    public static final int MODE_DASHU = 2;
    public static final int MODE_JINGSONG = 3;
    public static final int MODE_GAOGUAI = 4;
    public static final int MODE_KONGLING = 5;

    /**
     * 音效处理
     *
     * @param path 文件路径
     * @param type 音效类型
     */
    public native static void change(String path, int type);

    static {
        System.loadLibrary("voice_change");
    }
}
