package com.icytown.course.experimentone.handler;

import android.content.Context;
import android.content.DialogInterface;
import android.support.annotation.IdRes;
import android.support.v7.app.AlertDialog;
import android.text.TextUtils;
import android.view.View;
import android.widget.RadioGroup;
import android.widget.Toast;

import com.icytown.course.experimentone.R;
import com.icytown.course.experimentone.databinding.ActivityMainBinding;

public class MainHandler {

    private Context mContext;
    private ActivityMainBinding mBinding;

    public MainHandler(Context context, ActivityMainBinding binding) {
        mContext = context;
        mBinding = binding;
    }

    public void onClick(View v) {
        String text = mBinding.editText.getText().toString();
        if (TextUtils.isEmpty(text)) {
            Toast.makeText(mContext, "搜索内容不能为空", Toast.LENGTH_SHORT).show();
        } else {
            AlertDialog.Builder builder = new AlertDialog.Builder(mContext);
            builder.setTitle("提示")
                    .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            Toast.makeText(mContext, "对话框“取消”按钮被点击", Toast.LENGTH_SHORT).show();
                        }
                    })
                    .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            Toast.makeText(mContext, "对话框“确定”按钮被点击", Toast.LENGTH_SHORT).show();
                        }
                    });
            if (TextUtils.equals(text, "Health")) {
                builder.setTitle(getRadioButtonText(mBinding.radioGroup.getCheckedRadioButtonId()) + "搜索成功");
            } else {
                builder.setTitle("搜索失败");
            }
            builder.create().show();
        }
    }

    public void onCheckedChanged(RadioGroup group, @IdRes int checkedId) {
        String msg = getRadioButtonText(checkedId);
        if (TextUtils.isEmpty(msg)) {
            return;
        }
        Toast.makeText(mContext, msg + "被选中", Toast.LENGTH_SHORT).show();
    }

    private String getRadioButtonText(@IdRes int id) {
        switch (id) {
            case R.id.radioButtonImage: return mContext.getString(R.string.radioButtonImage);
            case R.id.radioButtonVideo: return mContext.getString(R.string.radioButtonVideo);
            case R.id.radioButtonFAQ: return mContext.getString(R.string.radioButtonFAQ);
            case R.id.radioButtonInfo: return mContext.getString(R.string.radioButtonInfo);
        }
        return "";
    }
}
