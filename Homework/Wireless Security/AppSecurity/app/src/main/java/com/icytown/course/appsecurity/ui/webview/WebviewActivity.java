package com.icytown.course.appsecurity.ui.webview;

import android.app.Activity;
import android.content.Intent;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import com.icytown.course.appsecurity.R;
import com.icytown.course.appsecurity.databinding.WebviewActivityBinding;

public class WebviewActivity extends AppCompatActivity {

    private WebviewActivityBinding binding;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = DataBindingUtil.setContentView(this, R.layout.webview_activity);
        binding.setHandler(new WebviewHandler(this, binding));
    }

    public static void startActivity(Activity activity) {
        Intent intent = new Intent(activity, WebviewActivity.class);
        activity.startActivity(intent);
    }
}
