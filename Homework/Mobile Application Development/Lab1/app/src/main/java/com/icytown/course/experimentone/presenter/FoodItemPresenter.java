package com.icytown.course.experimentone.presenter;

import android.content.Context;

import com.icytown.course.experimentone.context.FoodListActivity;
import com.icytown.course.experimentone.model.FoodItem;

public class FoodItemPresenter implements BaseFoodItemPresenter {

    public void onItemClick(Context context, FoodItem item) {
        ((FoodListActivity)context).getBinding().getHandler().turnToFoodDetailActivity(item, FoodListActivity.REQUESTCODE_RECYCLERVIEW);
    }

    public boolean onItemLongClick(Context context, FoodItem i) {
        return ((FoodListActivity)context).getBinding().getHandler().removeFromRecyclerView(i);
    }
}
