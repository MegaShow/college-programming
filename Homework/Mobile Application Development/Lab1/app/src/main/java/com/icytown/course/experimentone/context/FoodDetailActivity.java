package com.icytown.course.experimentone.context;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import com.icytown.course.experimentone.R;
import com.icytown.course.experimentone.databinding.ActivityFoodDetailBinding;
import com.icytown.course.experimentone.handler.FoodDetailHandler;
import com.icytown.course.experimentone.model.FoodItem;

public class FoodDetailActivity extends AppCompatActivity {

    private ActivityFoodDetailBinding binding;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = DataBindingUtil.setContentView(this, R.layout.activity_food_detail);
        binding.setModel(getExtraFoodItem());
        binding.executePendingBindings();
        binding.setHandler(new FoodDetailHandler(this, binding));

        getWindow().setStatusBarColor(binding.getModel().getColor());
    }

    @Override
    public void onBackPressed() {
        setResult(binding.getModel());
        super.onBackPressed();
    }

    public static void startActivityForResult(Context context, FoodItem item, int index, int requestCode) {
        Intent intent = new Intent(context, FoodDetailActivity.class);
        intent.putExtra("food", item);
        intent.putExtra("index", index);
        ((Activity) context).startActivityForResult(intent, requestCode);
    }

    public void setResult(FoodItem item) {
        Intent intent = new Intent();
        intent.putExtra("food", item);
        intent.putExtra("index", getExtraIndex());
        setResult(RESULT_OK, intent);
    }

    private FoodItem getExtraFoodItem() {
        return getIntent().getParcelableExtra("food");
    }

    private int getExtraIndex() {
        return getIntent().getIntExtra("index", -1);
    }
}
