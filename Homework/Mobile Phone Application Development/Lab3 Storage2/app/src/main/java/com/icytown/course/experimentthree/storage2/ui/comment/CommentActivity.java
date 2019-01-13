package com.icytown.course.experimentthree.storage2.ui.comment;

import android.app.Activity;
import android.content.Intent;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import com.icytown.course.experimentthree.storage2.R;
import com.icytown.course.experimentthree.storage2.databinding.CommentActivityBinding;

public class CommentActivity extends AppCompatActivity {

    private CommentActivityBinding binding;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = DataBindingUtil.setContentView(this, R.layout.comment_activity);
        binding.setHandler(new CommentHandler(this, binding, getUsername()));
    }

    private String getUsername() {
        return getIntent().getStringExtra("username");
    }

    public CommentActivityBinding getBinding() {
        return binding;
    }

    public static void startActivityAndFinish(Activity activity, String username) {
        Intent intent = new Intent(activity, CommentActivity.class);
        intent.putExtra("username", username);
        activity.startActivity(intent);
        activity.finish();
    }
}
