package com.icytown.course.appsecurity.ui.admin;

import android.support.annotation.IdRes;
import android.view.View;
import android.widget.RadioGroup;
import android.widget.Toast;

import com.icytown.course.appsecurity.data.database.StorageDatabase;
import com.icytown.course.appsecurity.data.model.User;
import com.icytown.course.appsecurity.ui.webview.WebviewActivity;
import com.icytown.course.appsecurity.R;
import com.icytown.course.appsecurity.databinding.AdminActivityBinding;

public class AdminHandler {

    private AdminActivity activity;
    private AdminActivityBinding binding;

    private StorageDatabase database;

    private int layoutId = R.id.radioLogin;

    AdminHandler(AdminActivity activity, AdminActivityBinding binding) {
        this.activity = activity;
        this.binding = binding;

        database = StorageDatabase.Helper.getDatabase(activity.getApplication());

        changeLayout(layoutId);
    }

    public void onCheckedChanged(RadioGroup group, @IdRes int id) {
        changeLayout(id);
    }

    public void onClickOk(View view) {
        if (layoutId == R.id.radioLogin) {
            String username = binding.editLoginName.getText().toString();
            String password = binding.editPassword.getText().toString();
            if (username.isEmpty()) {
                Toast.makeText(activity, "Username can't be empty.", Toast.LENGTH_SHORT).show();
                return;
            } else if (password.isEmpty()) {
                Toast.makeText(activity, "Password can't be empty.", Toast.LENGTH_SHORT).show();
                return;
            }
            User user = database.userDao().getUserByNameSync(username);
            if (user == null) {
                Toast.makeText(activity, "Username doesn't exist.", Toast.LENGTH_SHORT).show();
                return;
            } else if (!user.auth(password)) {
                Toast.makeText(activity, "Invalid password.", Toast.LENGTH_SHORT).show();
                return;
            }
            WebviewActivity.startActivity(activity);
        } else {
            String username = binding.editRegisterName.getText().toString();
            String newPassword = binding.editNewPassword.getText().toString();
            String confirmPassword = binding.editConfirmPassword.getText().toString();
            if (username.isEmpty()) {
                Toast.makeText(activity, "Username can't be empty.", Toast.LENGTH_SHORT).show();
                return;
            } else if (newPassword.isEmpty() || confirmPassword.isEmpty()) {
                Toast.makeText(activity, "Password can't be empty.", Toast.LENGTH_SHORT).show();
                return;
            } else if (!newPassword.equals(confirmPassword)) {
                Toast.makeText(activity, "Confirm password doesn't match.", Toast.LENGTH_SHORT).show();
                return;
            }
            User user = database.userDao().getUserByNameSync(username);
            if (user != null) {
                Toast.makeText(activity, "User already exists.", Toast.LENGTH_SHORT).show();
                return;
            }
            database.userDao().createUser(User.create(username, newPassword));
            Toast.makeText(activity, "Register successfully.", Toast.LENGTH_SHORT).show();
        }
    }

    public void onClickClear(View view) {
        clearLayout();
    }

    private void changeLayout(@IdRes int id) {
        layoutId = id;
        clearLayout();
        if (layoutId == R.id.radioLogin) {
            String username = binding.editRegisterName.getText().toString();
            binding.editLoginName.setText(username);
            binding.layoutLogin.setVisibility(View.VISIBLE);
            binding.layoutRegister.setVisibility(View.GONE);
        } else {
            String username = binding.editLoginName.getText().toString();
            binding.editRegisterName.setText(username);
            binding.layoutLogin.setVisibility(View.GONE);
            binding.layoutRegister.setVisibility(View.VISIBLE);
        }
    }

    private void clearLayout() {
        if (layoutId == R.id.radioLogin) {
            binding.editLoginName.getText().clear();
            binding.editPassword.getText().clear();
        } else {
            binding.editRegisterName.getText().clear();
            binding.editNewPassword.getText().clear();
            binding.editConfirmPassword.getText().clear();
        }
    }
}
