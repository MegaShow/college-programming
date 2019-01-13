package com.icytown.course.experimentthree.storage2.ui.comment;

import android.content.Context;

import com.icytown.course.experimentthree.storage2.data.model.Comment;
import com.icytown.course.experimentthree.storage2.data.model.CommentLike;
import com.icytown.course.experimentthree.storage2.data.model.Item;

public class Presenter {

    public void onItemClick(Context context, Comment comment) {
        ((CommentActivity) context).getBinding().getHandler().showInfo(comment.username);
    }

    public boolean onItemLongClick(Context context, Comment comment) {
        return ((CommentActivity) context).getBinding().getHandler().deleteOrReport(comment);
    }

    public void onClickLike(Context context, Item item) {
        ((CommentActivity) context).getBinding().getHandler().likeOrDislike(item);
    }
}
