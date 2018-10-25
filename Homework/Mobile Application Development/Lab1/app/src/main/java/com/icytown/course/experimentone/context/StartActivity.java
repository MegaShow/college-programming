package com.icytown.course.experimentone.context;

import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import com.icytown.course.experimentone.R;
import com.icytown.course.experimentone.databinding.ActivityStartBinding;
import com.icytown.course.experimentone.handler.StartHandler;

public class StartActivity extends AppCompatActivity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ActivityStartBinding binding = DataBindingUtil.setContentView(this, R.layout.activity_start);
        binding.setHandler(new StartHandler(this, binding));
    }
}
