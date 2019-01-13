package com.icytown.course.experimenttwo.presentation;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import com.icytown.course.experimenttwo.presentation.foodlist.FoodListActivity;

public class LauncherActivity extends AppCompatActivity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        FoodListActivity.startActivity(this);
        finish();
    }
}
