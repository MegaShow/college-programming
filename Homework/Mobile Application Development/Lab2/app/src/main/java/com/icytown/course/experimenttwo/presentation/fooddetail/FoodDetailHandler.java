package com.icytown.course.experimenttwo.presentation.fooddetail;

import android.app.Activity;
import android.content.Context;
import android.util.Pair;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Toast;

import com.icytown.course.experimenttwo.R;
import com.icytown.course.experimenttwo.databinding.ActivityFoodDetailBinding;
import com.icytown.course.experimenttwo.receiver.DynamicReceiver;
import com.icytown.course.experimenttwo.receiver.WidgetProvider;

import org.greenrobot.eventbus.EventBus;

public class FoodDetailHandler {

    private Context mContext;
    private ActivityFoodDetailBinding mBinding;

    private int index;

    private final String[] listViewData = {
            "分享信息", "不感兴趣", "查看更多信息", "出错反馈"
    };

    public FoodDetailHandler(Context context, ActivityFoodDetailBinding binding, int index) {
        mContext = context;
        mBinding = binding;

        this.index = index;

        initListView();
    }

    public void onClickBack(View view) {
        ((Activity) mContext).finish();
    }

    public void onClickStar(View view) {
        if (mBinding.getModel().isStar()) {
            mBinding.getModel().setStar(false);
        } else {
            mBinding.getModel().setStar(true);
        }
        EventBus.getDefault().post(new Pair<>(mBinding.getModel(), index));
    }

    public void onClickCollect(View view) {
        if (mBinding.getModel().isCollect()) {
            Toast.makeText(mContext, "不可重复收藏", Toast.LENGTH_SHORT).show();
        } else {
            mBinding.getModel().setCollect(true);
            Toast.makeText(mContext, "已收藏", Toast.LENGTH_SHORT).show();
            EventBus.getDefault().post(new Pair<>(mBinding.getModel(), index));
            DynamicReceiver.sendDynamicAction(mContext, mBinding.getModel(), index);
            WidgetProvider.sendDynamicAction(mContext, mBinding.getModel(), index);
        }
    }

    private void initListView() {
        ArrayAdapter<String> adapter = new ArrayAdapter<>(mContext, R.layout.simple_list_item, listViewData);
        mBinding.menu.setAdapter(adapter);
    }

    public void setIndex(int index) {
        this.index = index;
    }
}
