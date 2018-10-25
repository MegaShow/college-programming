package com.icytown.course.experimentone.handler;

import android.content.Context;
import android.view.View;

import com.icytown.course.experimentone.context.FoodListActivity;
import com.icytown.course.experimentone.context.MainActivity;
import com.icytown.course.experimentone.databinding.ActivityStartBinding;


public class StartHandler {

    private Context mContext;
    private ActivityStartBinding mBinding;

    public StartHandler(Context context, ActivityStartBinding binding) {
        mContext = context;
        mBinding = binding;
    }

    public void onClickToMainActivity(View view) {
        MainActivity.startActivity(mContext);
    }

    public void onClickToListActivity(View view) {
        FoodListActivity.startActivity(mContext);
    }
}
