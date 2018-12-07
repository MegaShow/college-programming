package com.icytown.course.experimentfour.musicplayer;

import android.Manifest;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.databinding.DataBindingUtil;
import android.net.Uri;
import android.os.Bundle;
import android.os.IBinder;
import android.preference.PreferenceManager;
import android.provider.MediaStore;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;

import com.icytown.course.experimentfour.musicplayer.databinding.MusicActivityBinding;

import java.io.File;

public class MusicActivity extends AppCompatActivity {

    private MusicActivityBinding binding;
    private MusicServiceConnection connection;

    public void stopService() {
        Intent intent = new Intent(this, MusicService.class);
        stopService(intent);
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        if (ContextCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, 1);
        }

        binding = DataBindingUtil.setContentView(this, R.layout.music_activity);
        binding.setHandler(new MusicHandler(this, binding));

        Intent intent = new Intent(this, MusicService.class);
        connection = new MusicServiceConnection();
        startService(intent);
        bindService(intent, connection, BIND_AUTO_CREATE);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        SharedPreferences.Editor editor = PreferenceManager.getDefaultSharedPreferences(this).edit();
        editor.putFloat("rotate", binding.musicImage.getRotation());
        editor.apply();
        unbindService(connection);

        binding.getHandler().close();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (data == null) {
            return;
        }
        switch (requestCode) {
            case 1:
                if (resultCode == RESULT_OK) {
                    Uri uri = data.getData();
                    if (uri != null) {
                        binding.getHandler().afterClickOpen(new File(getRealPathFromURI(uri)), true);
                    }
                }
                break;
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        switch (requestCode) {
            case 1:
                for (int i = 0; i < permissions.length; i++) {
                    switch (permissions[i]) {
                        case Manifest.permission.READ_EXTERNAL_STORAGE:
                            if (grantResults[i] != PackageManager.PERMISSION_GRANTED) {
                                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, 1);
                            }
                    }
                }
        }
    }

    class MusicServiceConnection implements ServiceConnection {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            binding.getHandler().setBinder((MusicService.MusicBinder) service);
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
        }
    }

    public String getRealPathFromURI(Uri contentUri) {
        String res = null;
        String[] proj = {MediaStore.Audio.Media.DATA};
        Cursor cursor = getContentResolver().query(contentUri, proj, null, null, null);
        if (null != cursor && cursor.moveToFirst()) {
            int column_index = cursor.getColumnIndexOrThrow(MediaStore.Audio.Media.DATA);
            res = cursor.getString(column_index);
            cursor.close();
        }
        return res;
    }
}
