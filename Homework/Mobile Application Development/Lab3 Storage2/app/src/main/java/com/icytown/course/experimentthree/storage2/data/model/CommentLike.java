package com.icytown.course.experimentthree.storage2.data.model;

import android.arch.persistence.room.ColumnInfo;
import android.arch.persistence.room.Entity;
import android.arch.persistence.room.ForeignKey;
import android.arch.persistence.room.Index;
import android.support.annotation.NonNull;

@Entity(primaryKeys = {"username", "commentId"}, foreignKeys = {
        @ForeignKey(entity = User.class, parentColumns = "name", childColumns = "username", onDelete = ForeignKey.CASCADE),
        @ForeignKey(entity = Comment.class, parentColumns = "id", childColumns = "commentId", onDelete = ForeignKey.CASCADE)
}, indices = {
        @Index(value = "username"),
        @Index(value = "commentId")
})
public class CommentLike {

    @NonNull
    public String username;
    public int commentId;

    public CommentLike(@NonNull String username, int commentId) {
        this.username = username;
        this.commentId = commentId;
    }
}
