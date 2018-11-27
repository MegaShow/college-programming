package com.icytown.course.experimentthree.storage2.data.dao;

import android.arch.persistence.room.Dao;
import android.arch.persistence.room.Delete;
import android.arch.persistence.room.Insert;

import com.icytown.course.experimentthree.storage2.data.model.CommentLike;

@Dao
public interface LikeDao {

    @Insert
    void createLike(CommentLike commentLike);

    @Delete
    void deleteLike(CommentLike commentLike);
}
