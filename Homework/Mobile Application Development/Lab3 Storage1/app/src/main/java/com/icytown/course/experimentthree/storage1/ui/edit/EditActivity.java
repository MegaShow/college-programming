package com.icytown.course.experimentthree.storage1.ui.edit;

import android.content.Context;
import android.content.Intent;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import com.icytown.course.experimentthree.storage1.R;
import com.icytown.course.experimentthree.storage1.databinding.ActivityEditBinding;

public class EditActivity extends AppCompatActivity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ActivityEditBinding binding = DataBindingUtil.setContentView(this, R.layout.activity_edit);
        binding.setHandler(new EditHandler(this, binding));
    }

    public static void startActivity(Context context) {
        Intent intent = new Intent(context, EditActivity.class);
        context.startActivity(intent);
    }
}
