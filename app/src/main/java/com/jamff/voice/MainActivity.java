package com.jamff.voice;

import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import org.fmod.FMOD;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private static final String PATH = "file:///android_asset/voice.m4a";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
        initData();
    }

    private void initView() {
        findViewById(R.id.tv_record).setOnClickListener(this);
        findViewById(R.id.tv_luoli).setOnClickListener(this);
        findViewById(R.id.tv_dashu).setOnClickListener(this);
        findViewById(R.id.tv_jingsong).setOnClickListener(this);
        findViewById(R.id.tv_gaoguai).setOnClickListener(this);
        findViewById(R.id.tv_kongling).setOnClickListener(this);
    }

    private void initData() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            String[] perms = {"android.permission.RECORD_AUDIO", "android.permission.WRITE_EXTERNAL_STORAGE"};
            if (checkSelfPermission(perms[0]) == PackageManager.PERMISSION_DENIED ||
                    checkSelfPermission(perms[1]) == PackageManager.PERMISSION_DENIED) {
                requestPermissions(perms, 200);
            }
        }
        FMOD.init(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.tv_record:
                EffectUtils.change(PATH, EffectUtils.MODE_NORMAL);
                break;
            case R.id.tv_luoli:
                EffectUtils.change(PATH, EffectUtils.MODE_LUOLI);
                break;
            case R.id.tv_dashu:
                EffectUtils.change(PATH, EffectUtils.MODE_DASHU);
                break;
            case R.id.tv_jingsong:
                EffectUtils.change(PATH, EffectUtils.MODE_JINGSONG);
                break;
            case R.id.tv_gaoguai:
                EffectUtils.change(PATH, EffectUtils.MODE_GAOGUAI);
                break;
            case R.id.tv_kongling:
                EffectUtils.change(PATH, EffectUtils.MODE_KONGLING);
                break;
        }
    }

    @Override
    protected void onDestroy() {
        FMOD.close();
        super.onDestroy();
    }
}
