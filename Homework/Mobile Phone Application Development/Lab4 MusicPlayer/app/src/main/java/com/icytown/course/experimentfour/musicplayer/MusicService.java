package com.icytown.course.experimentfour.musicplayer;

import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Binder;
import android.os.IBinder;
import android.os.Parcel;
import android.os.RemoteException;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;

import java.io.File;
import java.io.IOException;
import java.util.concurrent.TimeUnit;

import io.reactivex.Observable;
import io.reactivex.ObservableEmitter;
import io.reactivex.ObservableOnSubscribe;
import io.reactivex.Scheduler;
import io.reactivex.schedulers.Schedulers;

public class MusicService extends Service {

    private MediaPlayer mediaPlayer;
    private MusicBinder binder;

    private File file;
    private boolean isInit;

    @Override
    public void onCreate() {
        super.onCreate();

        mediaPlayer = new MediaPlayer();
        binder = new MusicBinder();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();

        if (mediaPlayer != null) {
            mediaPlayer.stop();
            mediaPlayer.release();
        }
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return binder;
    }

    public class MusicBinder extends Binder {

        public final static int PLAY = 1;
        public final static int PAUSE = 2;
        public final static int STOP = 3;
        public final static int OPEN = 4;
        public final static int GET_FILE = 5;
        public final static int IS_PLAYING = 6;
        public final static int SET_TIME = 7;
        public final static int GET_TIME = 8;

        @Override
        protected boolean onTransact(int code, @NonNull Parcel data, @Nullable Parcel reply, int flags) throws RemoteException {
            boolean flag;
            switch (code) {
                case PLAY:
                    flag = play();
                    if (reply != null) {
                        reply.writeBooleanArray(new boolean[]{flag});
                    }
                    break;
                case PAUSE:
                    flag = pause();
                    if (reply != null) {
                        reply.writeBooleanArray(new boolean[]{flag});
                    }
                    break;
                case STOP:
                    stop();
                    break;
                case OPEN:
                    open(new File(data.readString()));
                    break;
                case GET_FILE:
                    if (reply != null) {
                        if (file != null) {
                            reply.writeString(file.getAbsolutePath());
                        }
                    }
                    break;
                case IS_PLAYING:
                    flag = isPlaying();
                    if (reply != null) {
                        reply.writeBooleanArray(new boolean[]{flag});
                    }
                    break;
                case SET_TIME:
                    setTime(data.readInt());
                    break;
                case GET_TIME:
                    if (reply != null) {
                        reply.writeInt(getTime());
                    }
                    break;
            }
            return super.onTransact(code, data, reply, flags);
        }
    }

    private int getTime() {
        return mediaPlayer.getCurrentPosition() / 1000;
    }

    private void setTime(int time) {
        mediaPlayer.seekTo(time * 1000);
    }

    private boolean play() {
        if (isInit && !mediaPlayer.isPlaying()) {
            mediaPlayer.start();
            return true;
        }
        return false;
    }

    private boolean pause() {
        if (isInit && mediaPlayer.isPlaying()) {
            mediaPlayer.pause();
            return true;
        }
        return false;
    }

    private void stop() {
        mediaPlayer.reset();
        init();
    }

    private void open(File newFile) {
        file = newFile;
        stop();
    }

    private boolean isPlaying() {
        return mediaPlayer.isPlaying();
    }

    private void init() {
        try {
            isInit = false;
            mediaPlayer.setDataSource(file.getPath());
            mediaPlayer.setOnPreparedListener(mp -> isInit = true);
            mediaPlayer.setOnCompletionListener(mp -> stop());
            mediaPlayer.prepareAsync();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
