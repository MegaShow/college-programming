package com.icytown.course.experimentthree.storage2.data.dao;

import android.arch.lifecycle.LiveData;
import android.arch.persistence.room.Dao;
import android.arch.persistence.room.Delete;
import android.arch.persistence.room.Insert;
import android.arch.persistence.room.Query;
import android.arch.persistence.room.Update;

import com.icytown.course.experimentthree.storage2.data.model.Comment;
import com.icytown.course.experimentthree.storage2.data.model.Item;

import java.util.List;

@Dao
public interface CommentDao {

    @Query("SELECT u.*, c.*, l.commentId AS isLike " +
            "FROM User u, Comment c " +
            "LEFT JOIN CommentLike l ON l.username = :username AND l.commentId = c.id " +
            "WHERE u.name = c.username " +
            "ORDER BY c.date")
    LiveData<List<Item>> getAllItems(String username);

    @Insert
    void createComment(Comment comment);

    @Delete
    void deleteComment(Comment comment);

    @Update
    void updateComment(Comment comment);
}
