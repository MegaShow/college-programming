package com.icytown.course.experimentthree.storage2.data.model;

import android.arch.persistence.room.Entity;
import android.arch.persistence.room.PrimaryKey;
import android.arch.persistence.room.TypeConverters;
import android.graphics.Bitmap;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;

import com.icytown.course.experimentthree.storage2.data.common.BitmapConverter;

@Entity
@TypeConverters(value = {BitmapConverter.class})
public class User {

    @PrimaryKey
    @NonNull
    public String name;

    @NonNull
    public String password;

    @Nullable
    public Bitmap avatar;

    public User(@NonNull String name, @NonNull String password, Bitmap avatar) {
        this.name = name;
        this.password = password;
        this.avatar = avatar;
    }

    public boolean auth(@NonNull String password) {
        return this.password.equals(password);
    }
}
