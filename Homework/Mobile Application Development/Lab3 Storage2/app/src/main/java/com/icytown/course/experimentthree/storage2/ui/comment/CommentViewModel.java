package com.icytown.course.experimentthree.storage2.ui.comment;

import android.app.Application;
import android.arch.lifecycle.AndroidViewModel;
import android.arch.lifecycle.LiveData;

import com.icytown.course.experimentthree.storage2.data.database.StorageDatabase;
import com.icytown.course.experimentthree.storage2.data.model.Comment;
import com.icytown.course.experimentthree.storage2.data.model.CommentLike;
import com.icytown.course.experimentthree.storage2.data.model.Item;

import java.util.List;

public class CommentViewModel extends AndroidViewModel {

    private StorageDatabase database;
    private LiveData<List<Item>> comments;

    public CommentViewModel(Application app) {
        super(app);

        database = StorageDatabase.Helper.getDatabase(app);
    }

    LiveData<List<Item>> getAllItems(String username) {
        if (comments == null) {
            comments = database.commentDao().getAllItems(username);
        }
        return comments;
    }

    void createComment(Comment comment) {
        database.commentDao().createComment(comment);
    }

    void deleteComment(Comment comment) {
        database.commentDao().deleteComment(comment);
    }

    void updateComment(Comment comment) {
        database.commentDao().updateComment(comment);
    }

    void createLike(CommentLike commentLike) {
        database.likeDao().createLike(commentLike);
    }

    void deleteLike(CommentLike commentLike) {
        database.likeDao().deleteLike(commentLike);
    }
}
