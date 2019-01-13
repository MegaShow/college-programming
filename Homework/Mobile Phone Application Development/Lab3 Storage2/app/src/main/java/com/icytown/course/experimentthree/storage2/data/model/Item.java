package com.icytown.course.experimentthree.storage2.data.model;

import android.arch.persistence.room.Embedded;
import android.arch.persistence.room.Entity;

@Entity
public class Item {

    @Embedded
    public User user;

    @Embedded
    public Comment comment;

    public boolean isLike;
}
