package com.icytown.course.experimenttwo.presentation.foodlist;

import android.content.Context;

import com.icytown.course.experimenttwo.data.model.FoodItem;

public interface BaseFoodItemPresenter {

    void onItemClick(Context context, FoodItem item);

    boolean onItemLongClick(Context context, FoodItem item);
}
