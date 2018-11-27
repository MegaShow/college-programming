package com.icytown.course.experimentthree.storage1.ui.admin;

import android.content.SharedPreferences;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import com.icytown.course.experimentthree.storage1.R;
import com.icytown.course.experimentthree.storage1.databinding.ActivityLoginBinding;
import com.icytown.course.experimentthree.storage1.databinding.ActivityRegisterBinding;

import java.util.Objects;

public class AdminActivity extends AppCompatActivity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(this);
        if (Objects.requireNonNull(pref.getString("password", "")).equals("")) {
            ActivityRegisterBinding binding = DataBindingUtil.setContentView(this, R.layout.activity_register);
            binding.setHandler(new RegisterHandler(this, binding));
        } else {
            ActivityLoginBinding binding = DataBindingUtil.setContentView(this, R.layout.activity_login);
            binding.setHandler(new LoginHandler(this, binding));
        }
    }
}
