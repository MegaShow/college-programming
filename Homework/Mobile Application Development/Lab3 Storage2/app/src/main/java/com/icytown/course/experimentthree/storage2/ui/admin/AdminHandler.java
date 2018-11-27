package com.icytown.course.experimentthree.storage2.ui.admin;

import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.provider.MediaStore;
import android.support.annotation.IdRes;
import android.view.View;
import android.widget.RadioGroup;
import android.widget.Toast;

import com.icytown.course.experimentthree.storage2.R;
import com.icytown.course.experimentthree.storage2.data.database.StorageDatabase;
import com.icytown.course.experimentthree.storage2.data.model.User;
import com.icytown.course.experimentthree.storage2.databinding.AdminActivityBinding;
import com.icytown.course.experimentthree.storage2.ui.comment.CommentActivity;

import java.io.IOException;

public class AdminHandler {

    private AdminActivity activity;
    private AdminActivityBinding binding;

    private StorageDatabase database;

    private int layoutId = R.id.radioLogin;
    private Bitmap avatar;

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
            CommentActivity.startActivityAndFinish(activity, username);
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
            database.userDao().createUser(new User(username, newPassword, avatar));
            Toast.makeText(activity, "Register successfully.", Toast.LENGTH_SHORT).show();
        }
    }

    public void onClickClear(View view) {
        clearLayout();
    }

    public void onClickEditAvatar(View view) {
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.setType("image/*");
        activity.startActivityForResult(intent, 1);
    }

    void changeAvatar(Uri uri) {
        try {
            Bitmap bitmap = MediaStore.Images.Media.getBitmap(activity.getContentResolver(), uri);
            final int width, height;
            if (bitmap.getWidth() < bitmap.getHeight()) {
                width = bitmap.getWidth() * 256 / bitmap.getHeight();
                height = 256;
            } else {
                width = 256;
                height = bitmap.getHeight() * 256 / bitmap.getWidth();
            }
            avatar = Bitmap.createScaledBitmap(bitmap, width, height, false);
            binding.editAvatar.setImageBitmap(avatar);
        } catch (IOException e) {
            e.printStackTrace();
            Toast.makeText(activity, "Some errors happened.", Toast.LENGTH_SHORT).show();
        }
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
            avatar = null;
            binding.editAvatar.setImageResource(R.mipmap.add);
            binding.editRegisterName.getText().clear();
            binding.editNewPassword.getText().clear();
            binding.editConfirmPassword.getText().clear();
        }
    }
}
