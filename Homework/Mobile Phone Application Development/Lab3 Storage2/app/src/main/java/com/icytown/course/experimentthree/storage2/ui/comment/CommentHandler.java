package com.icytown.course.experimentthree.storage2.ui.comment;

import android.Manifest;
import android.arch.lifecycle.Observer;
import android.arch.lifecycle.ViewModelProvider;
import android.arch.lifecycle.ViewModelProviders;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.provider.ContactsContract;
import android.support.annotation.Nullable;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.view.View;
import android.widget.Toast;

import com.icytown.course.experimentthree.storage2.R;
import com.icytown.course.experimentthree.storage2.data.model.Comment;
import com.icytown.course.experimentthree.storage2.data.model.CommentLike;
import com.icytown.course.experimentthree.storage2.data.model.Item;
import com.icytown.course.experimentthree.storage2.databinding.CommentActivityBinding;

import java.util.Date;
import java.util.List;

public class CommentHandler {

    private static final String TAG = "CommentHandler";

    private CommentActivity activity;
    private CommentActivityBinding binding;
    private CommentViewModel viewModel;
    private String username;

    private ListAdapter adapter;

    CommentHandler(final CommentActivity activity, final CommentActivityBinding binding, final String username) {
        this.activity = activity;
        this.binding = binding;
        this.username = username;

        viewModel = ViewModelProviders.of(activity, ViewModelProvider.AndroidViewModelFactory.getInstance(activity.getApplication())).get(CommentViewModel.class);

        viewModel.getAllItems(username).observe(activity, new Observer<List<Item>>() {
            @Override
            public void onChanged(@Nullable List<Item> items) {
                if (items != null && adapter == null) {
                    adapter = new ListAdapter(activity, R.layout.comment_item, items);
                    binding.list.setAdapter(adapter);
                }
            }
        });
    }

    public void onClickSend(View view) {
        String text = binding.editComment.getText().toString();
        if (text.isEmpty()) {
            Toast.makeText(activity, "Comment can't be empty.", Toast.LENGTH_SHORT).show();
            return;
        }
        adapter = null;
        viewModel.createComment(new Comment(username, text, new Date(), 0));
        Toast.makeText(activity, "Send successfully.", Toast.LENGTH_SHORT).show();
        binding.editComment.getText().clear();
    }

    void showInfo(String username) {
        if (ContextCompat.checkSelfPermission(activity, Manifest.permission.READ_CONTACTS) != PackageManager.PERMISSION_GRANTED) {
            Toast.makeText(activity, "No read contacts permission.", Toast.LENGTH_LONG).show();
            return;
        }
        Cursor cursor = activity.getContentResolver().query(
                ContactsContract.CommonDataKinds.Phone.CONTENT_URI,
                new String[]{ContactsContract.CommonDataKinds.Phone.NUMBER},
                ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME + "=?",
                new String[]{username},
                null
        );
        StringBuilder phone = new StringBuilder();
        if (cursor != null) {
            boolean flag = cursor.moveToFirst();
            if (flag) {
                while (flag || cursor.moveToNext()) {
                    flag = false;
                    phone.append("\nPhone: ");
                    phone.append(cursor.getString(cursor.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER)));
                }
            } else {
                phone.append("\nPhone number not exist.");
            }
            cursor.close();
        } else {
            phone.append("\nPhone number not exist.");
        }
        AlertDialog.Builder builder = new AlertDialog.Builder(activity)
                .setTitle("Info")
                .setMessage("Username: " + username + phone.toString())
                .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                    }
                });
        builder.create().show();
    }

    boolean deleteOrReport(final Comment comment) {
        if (username.equals(comment.username)) {
            AlertDialog.Builder builder = new AlertDialog.Builder(activity)
                    .setTitle("Delete or not?")
                    .setNegativeButton("NO", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                        }
                    })
                    .setPositiveButton("YES", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            adapter = null;
                            viewModel.deleteComment(comment);
                        }
                    });
            builder.create().show();
        } else {
            AlertDialog.Builder builder = new AlertDialog.Builder(activity)
                    .setTitle("Report or not?")
                    .setNegativeButton("NO", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                        }
                    })
                    .setPositiveButton("YES", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            Toast.makeText(activity, "Report successfully.", Toast.LENGTH_SHORT).show();
                        }
                    });
            builder.create().show();
        }
        return true;
    }

    void likeOrDislike(Item item) {
        if (item.isLike) {
            viewModel.deleteLike(new CommentLike(username, item.comment.id));
            item.comment.like--;
            item.isLike = false;
        } else {
            viewModel.createLike(new CommentLike(username, item.comment.id));
            item.comment.like++;
            item.isLike = true;
        }
        viewModel.updateComment(item.comment);
        adapter.notifyDataSetChanged();
    }
}
