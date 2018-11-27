package com.icytown.course.experimentthree.storage2.data.model;

import android.arch.persistence.room.Entity;
import android.arch.persistence.room.ForeignKey;
import android.arch.persistence.room.Index;
import android.arch.persistence.room.PrimaryKey;
import android.arch.persistence.room.TypeConverters;

import com.icytown.course.experimentthree.storage2.data.common.DateConverter;

import java.util.Date;

@Entity(foreignKeys = {
        @ForeignKey(entity = User.class, parentColumns = "name", childColumns = "username", onDelete = ForeignKey.CASCADE)
}, indices = {
        @Index(value = {"username"})
})
@TypeConverters({DateConverter.class})
public class Comment {

    @PrimaryKey(autoGenerate = true)
    public int id;

    public String username;
    public String text;
    public Date date;
    public int like;

    public Comment() {}

    public Comment(String username, String text, Date data, int like) {
        this.username = username;
        this.text = text;
        this.date = data;
        this.like = like;
    }
}
