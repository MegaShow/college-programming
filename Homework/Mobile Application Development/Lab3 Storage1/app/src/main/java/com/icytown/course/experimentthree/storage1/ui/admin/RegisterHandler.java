package com.icytown.course.experimentthree.storage1.ui.admin;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.view.View;
import android.widget.Toast;

import com.icytown.course.experimentthree.storage1.databinding.ActivityRegisterBinding;
import com.icytown.course.experimentthree.storage1.ui.edit.EditActivity;

public class RegisterHandler {

    private Context mContext;
    private ActivityRegisterBinding mBinding;

    RegisterHandler(Context context, ActivityRegisterBinding binding) {
        mContext = context;
        mBinding = binding;
    }

    public void onClickButtonOk(View view) {
        String newPassword = mBinding.newPassword.getText().toString();
        String confirmPassword = mBinding.confirmPassword.getText().toString();
        if (newPassword.isEmpty() || confirmPassword.isEmpty()) {
            Toast.makeText(mContext, "Password cannot be empty.", Toast.LENGTH_SHORT).show();
        } else if (newPassword.equals(confirmPassword)) {
            SharedPreferences.Editor editor = PreferenceManager.getDefaultSharedPreferences(mContext).edit();
            editor.putString("password", newPassword);
            editor.apply();
            EditActivity.startActivity(mContext);
        } else {
            Toast.makeText(mContext, "Password mismatch.", Toast.LENGTH_SHORT).show();
        }
    }

    public void onClickButtonClear(View view) {
        mBinding.newPassword.getText().clear();
        mBinding.confirmPassword.getText().clear();
    }
}
