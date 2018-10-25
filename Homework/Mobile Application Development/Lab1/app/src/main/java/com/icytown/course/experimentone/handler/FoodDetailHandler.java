package com.icytown.course.experimentone.handler;

import android.content.Context;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Toast;

import com.icytown.course.experimentone.R;
import com.icytown.course.experimentone.context.FoodDetailActivity;
import com.icytown.course.experimentone.databinding.ActivityFoodDetailBinding;

public class FoodDetailHandler {

    private Context mContext;
    private ActivityFoodDetailBinding mBinding;

    private final String[] listViewData = {
            "分享信息", "不感兴趣", "查看更多信息", "出错反馈"
    };

    public FoodDetailHandler(Context context, ActivityFoodDetailBinding binding) {
        mContext = context;
        mBinding = binding;

        initListView();
    }

    public void onClickBack(View view) {
        FoodDetailActivity activity = (FoodDetailActivity) mContext;
        activity.setResult(mBinding.getModel());
        activity.finish();
    }

    public void onClickStar(View view) {
        if (mBinding.getModel().isStar()) {
            mBinding.getModel().setStar(false);
        } else {
            mBinding.getModel().setStar(true);
        }
    }

    public void onClickCollect(View view) {
        if (mBinding.getModel().isCollect()) {
            Toast.makeText(mContext, "不可重复收藏", Toast.LENGTH_SHORT).show();
        } else {
            mBinding.getModel().setCollect(true);
            Toast.makeText(mContext, "已收藏", Toast.LENGTH_SHORT).show();
        }
    }

    private void initListView() {
        ArrayAdapter<String> adapter = new ArrayAdapter<>(mContext, R.layout.simple_list_item, listViewData);
        mBinding.menu.setAdapter(adapter);
    }
}
