package com.icytown.course.appsecurity.ui.admin;

import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import com.icytown.course.appsecurity.R;
import com.icytown.course.appsecurity.databinding.AdminActivityBinding;

public class AdminActivity extends AppCompatActivity {

    private AdminHandler handler;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        AdminActivityBinding binding = DataBindingUtil.setContentView(this, R.layout.admin_activity);
        handler = new AdminHandler(this, binding);
        binding.setHandler(handler);
    }
}
