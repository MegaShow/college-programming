package com.icytown.course.experimentone.presenter;

import android.content.Context;

import com.icytown.course.experimentone.model.FoodItem;

public interface BaseFoodItemPresenter {

    void onItemClick(Context context, FoodItem item);

    boolean onItemLongClick(Context context, FoodItem item);
}
