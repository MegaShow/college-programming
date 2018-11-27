package com.icytown.course.experimentthree.storage1.ui.admin;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.view.View;
import android.widget.Toast;

import com.icytown.course.experimentthree.storage1.databinding.ActivityLoginBinding;
import com.icytown.course.experimentthree.storage1.ui.edit.EditActivity;

import java.util.Objects;

public class LoginHandler {

    private Context mContext;
    private ActivityLoginBinding mBinding;

    LoginHandler(Context context, ActivityLoginBinding binding) {
        mContext = context;
        mBinding = binding;
    }

    public void onClickButtonOk(View view) {
        String password = mBinding.password.getText().toString();
        if (password.isEmpty()) {
            Toast.makeText(mContext, "Password cannot be empty.", Toast.LENGTH_SHORT).show();
            return;
        }
        SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(mContext);
        if (Objects.requireNonNull(pref.getString("password", "")).equals(password)) {
            EditActivity.startActivity(mContext);
        } else {
            Toast.makeText(mContext, "Invalid password.", Toast.LENGTH_SHORT).show();
        }
    }

    public void onClickButtonClear(View view) {
        mBinding.password.getText().clear();
    }
}
