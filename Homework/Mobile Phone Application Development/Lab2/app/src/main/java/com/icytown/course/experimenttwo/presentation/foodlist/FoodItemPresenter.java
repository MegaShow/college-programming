package com.icytown.course.experimenttwo.presentation.foodlist;

import android.content.Context;

import com.icytown.course.experimenttwo.data.model.FoodItem;

public class FoodItemPresenter implements BaseFoodItemPresenter {

    public void onItemClick(Context context, FoodItem item) {
        ((FoodListActivity)context).getBinding().getHandler().turnToFoodDetailActivity(item, FoodListActivity.REQUESTCODE_RECYCLERVIEW);
    }

    public boolean onItemLongClick(Context context, FoodItem i) {
        return ((FoodListActivity)context).getBinding().getHandler().removeFromRecyclerView(i);
    }
}
