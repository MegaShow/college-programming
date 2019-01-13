package com.icytown.course.experimenttwo.presentation.foodlist;

import android.content.Context;

import com.icytown.course.experimenttwo.data.model.FoodItem;

public class FoodCollectionItemPresenter implements BaseFoodItemPresenter {

    public void onItemClick(Context context, FoodItem item) {
        ((FoodListActivity) context).getBinding().getHandler().turnToFoodDetailActivity(item, FoodListActivity.REQUESTCODE_LISTVIEW);
    }

    public boolean onItemLongClick(Context context, FoodItem item) {
        return ((FoodListActivity) context).getBinding().getHandler().removeFromListView(item);
    }
}
