package com.icytown.course.experimentfour.musicplayer;

import android.animation.ObjectAnimator;
import android.animation.ValueAnimator;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaMetadataRetriever;
import android.os.Environment;
import android.os.Parcel;
import android.os.RemoteException;
import android.preference.PreferenceManager;
import android.view.View;
import android.view.animation.LinearInterpolator;
import android.widget.SeekBar;
import android.widget.Toast;

import com.icytown.course.experimentfour.musicplayer.databinding.MusicActivityBinding;

import java.io.File;
import java.util.Locale;
import java.util.concurrent.TimeUnit;

import io.reactivex.Observable;
import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.disposables.CompositeDisposable;
import io.reactivex.observers.DisposableObserver;
import io.reactivex.schedulers.Schedulers;

public class MusicHandler {

    private MusicActivity activity;
    private MusicActivityBinding binding;
    private MusicService.MusicBinder binder;

    private ObjectAnimator animator;

    private CompositeDisposable compositeDisposable = new CompositeDisposable();

    MusicHandler(MusicActivity activity, MusicActivityBinding binding) {
        this.activity = activity;
        this.binding = binding;
    }

    public void close() {
        compositeDisposable.clear();
    }

    public void setBinder(MusicService.MusicBinder binder) {
        this.binder = binder;
        Parcel reply = Parcel.obtain();
        try {
            binder.transact(MusicService.MusicBinder.GET_FILE, reply, reply, 0);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
        String name = reply.readString();
        File file = name == null ? null : new File(name);
        if (file == null) {
            File song = new File(Environment.getExternalStorageDirectory(), "/data/山高水长.mp3");
            if (!song.exists()) {
                Toast.makeText(activity, "歌曲【山高水长】不存在", Toast.LENGTH_LONG).show();
                activity.stopService();
                activity.finish();
                return;
            }
            afterClickOpen(song, true);
        } else {
            afterClickOpen(file, false);
        }
        Observable<Integer> observable = Observable.create(e -> {
            Parcel replyTime = Parcel.obtain();
            binder.transact(MusicService.MusicBinder.GET_TIME, replyTime, replyTime, 0);
            e.onNext(replyTime.readInt());
            e.onComplete();
        });
        DisposableObserver<Integer> disposableObserver = new DisposableObserver<Integer>() {
            @Override
            public void onNext(Integer time) {
                if (time == 0 && !isPlaying()) {
                    binding.buttonPlayOrPause.setImageResource(R.mipmap.play);
                    if (animator.isRunning()) {
                        resetAnimator(0.0f);
                    }
                }
                binding.musicNowTime.setText(String.format(Locale.getDefault(), "%02d:%02d", time / 60, time % 60));
                binding.musicSeekBar.setProgress(time);
            }

            @Override
            public void onError(Throwable e) {
            }

            @Override
            public void onComplete() {
            }
        };
        observable.observeOn(AndroidSchedulers.mainThread())
                .subscribeOn(Schedulers.io())
                .repeatWhen(o -> o.delay(1000, TimeUnit.MILLISECONDS))
                .subscribe(disposableObserver);
        compositeDisposable.add(disposableObserver);
    }

    public void onClickOpen(View view) {
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType("audio/*");
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        activity.startActivityForResult(intent, 1);
    }

    public void afterClickOpen(File file, boolean isOpen) {
        if (isOpen) {
            Parcel data = Parcel.obtain();
            data.writeString(file.getAbsolutePath());
            try {
                binder.transact(MusicService.MusicBinder.OPEN, data, null, 0);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
            resetAnimator(0.0f);
        } else {
            SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(activity);
            float value = pref.getFloat("rotate", 0.0f);
            resetAnimator(value);
            if (isPlaying()) {
                animator.resume();
            }
        }
        MediaMetadataRetriever mmr = new MediaMetadataRetriever();
        mmr.setDataSource(file.getPath());
        String title = mmr.extractMetadata(MediaMetadataRetriever.METADATA_KEY_TITLE);
        String author = mmr.extractMetadata(MediaMetadataRetriever.METADATA_KEY_ARTIST);
        int time = Integer.parseInt(mmr.extractMetadata(MediaMetadataRetriever.METADATA_KEY_DURATION));
        byte[] data = mmr.getEmbeddedPicture();
        mmr.release();
        Bitmap bitmap = BitmapFactory.decodeByteArray(data, 0, data.length);
        binding.musicTitle.setText(title != null && !title.isEmpty() ? title : "未知");
        binding.musicAuthor.setText(author != null && !author.isEmpty() ? author : "未知");
        binding.musicTotalTime.setText(String.format(Locale.getDefault(), "%02d:%02d", time / 60000, time % 60000 / 1000));
        binding.musicSeekBar.setMax(time / 1000);
        if (bitmap == null) {
            binding.musicImage.setImageResource(R.mipmap.img);
        } else {
            binding.musicImage.setImageBitmap(bitmap);
        }
        binding.buttonPlayOrPause.setImageResource(isPlaying() ? R.mipmap.pause : R.mipmap.play);
    }

    public void onClickQuit(View view) {
        activity.stopService();
        activity.finish();
    }

    public void onClickPlayOrPause(View view) {
        if (isPlaying()) {
            Parcel reply = Parcel.obtain();
            try {
                binder.transact(MusicService.MusicBinder.PAUSE, reply, reply, 0);
                boolean[] flag = new boolean[1];
                reply.readBooleanArray(flag);
                if (flag[0]) {
                    binding.buttonPlayOrPause.setImageResource(R.mipmap.play);
                    binding.musicImage.setRotation(binding.musicImage.getRotation());
                    animator.pause();
                }
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        } else {
            Parcel reply = Parcel.obtain();
            try {
                binder.transact(MusicService.MusicBinder.PLAY, reply, reply, 0);
                boolean[] flag = new boolean[1];
                reply.readBooleanArray(flag);
                if (flag[0]) {
                    binding.buttonPlayOrPause.setImageResource(R.mipmap.pause);
                    animator.resume();
                }
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
    }

    public void onClickStop(View view) {
        Parcel reply = Parcel.obtain();
        try {
            binder.transact(MusicService.MusicBinder.STOP, reply, null, 0);
            binding.buttonPlayOrPause.setImageResource(R.mipmap.play);
            binding.musicNowTime.setText(activity.getString(R.string.zeroTime));
            binding.musicSeekBar.setProgress(0);
            resetAnimator(0.0f);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        if (fromUser) {
            Parcel data = Parcel.obtain();
            data.writeInt(progress);
            try {
                binder.transact(MusicService.MusicBinder.SET_TIME, data, null, 0);
                binding.musicNowTime.setText(String.format(Locale.getDefault(), "%02d:%02d", progress / 60, progress % 60));
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
    }

    private void resetAnimator(float value) {
        if (animator != null) {
            animator.end();
            binding.musicImage.clearAnimation();
        }
        animator = ObjectAnimator.ofFloat(binding.musicImage, "rotation", value, value + 360.0f);
        animator.setDuration(30000);
        animator.setInterpolator(new LinearInterpolator());
        animator.setRepeatCount(ValueAnimator.INFINITE);
        animator.start();
        animator.pause();
    }

    private boolean isPlaying() {
        Parcel reply = Parcel.obtain();
        try {
            binder.transact(MusicService.MusicBinder.IS_PLAYING, reply, reply, 0);
            boolean[] flag = new boolean[1];
            reply.readBooleanArray(flag);
            return flag[0];
        } catch (RemoteException e) {
            e.printStackTrace();
        }
        return false;
    }
}
