package com.icytown.course.experimentthree.storage1.ui.edit;

import android.content.Context;
import android.view.View;
import android.widget.Toast;

import com.icytown.course.experimentthree.storage1.databinding.ActivityEditBinding;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class EditHandler {

    private Context mContext;
    private ActivityEditBinding mBinding;

    EditHandler(Context context, ActivityEditBinding binding) {
        mContext = context;
        mBinding = binding;
    }

    public void onClickButtonSave(View view) {
        String text = mBinding.editText.getText().toString();
        if (text.isEmpty()) {
            Toast.makeText(mContext, "Editor cannot be empty.", Toast.LENGTH_SHORT).show();
            return;
        }
        try (FileOutputStream out = mContext.openFileOutput("data.txt", Context.MODE_PRIVATE)) {
            out.write(text.getBytes());
            Toast.makeText(mContext, "Save successfully.", Toast.LENGTH_SHORT).show();
        } catch (IOException e) {
            Toast.makeText(mContext, "Fail to save file.", Toast.LENGTH_SHORT).show();
        }
    }

    public void onClickButtonLoad(View view) {
        try (FileInputStream in = mContext.openFileInput("data.txt")) {
            byte[] contents = new byte[in.available()];
            in.read(contents);
            mBinding.editText.setText(new String(contents));
            Toast.makeText(mContext, "Load successfully.", Toast.LENGTH_SHORT).show();
        } catch (IOException e) {
            Toast.makeText(mContext, "Fail to load file.", Toast.LENGTH_SHORT).show();
        }
    }

    public void onClickButtonClear(View view) {
        mBinding.editText.getText().clear();
    }
}
