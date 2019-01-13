package com.icytown.course.experimenttwo.presentation.fooddetail;

import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import com.icytown.course.experimenttwo.R;
import com.icytown.course.experimenttwo.data.model.FoodItem;
import com.icytown.course.experimenttwo.databinding.ActivityFoodDetailBinding;
import com.icytown.course.experimenttwo.receiver.DynamicReceiver;
import com.icytown.course.experimenttwo.receiver.WidgetProvider;

public class FoodDetailActivity extends AppCompatActivity {

    private ActivityFoodDetailBinding binding;

    private final DynamicReceiver dynamicReceiver = new DynamicReceiver();
    private final IntentFilter dynamicFilter = new IntentFilter(DynamicReceiver.DYNAMIC_ACTION);
    private final WidgetProvider widgetProvider = new WidgetProvider();
    private final IntentFilter widgetFilter = new IntentFilter(WidgetProvider.DYNAMIC_ACTION);

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = DataBindingUtil.setContentView(this, R.layout.activity_food_detail);
        binding.setModel(getExtraFoodItem());
        binding.executePendingBindings();
        binding.setHandler(new FoodDetailHandler(this, binding, getExtraIndex()));

        getWindow().setStatusBarColor(binding.getModel().getColor());
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        setIntent(intent);
        binding.setModel(getExtraFoodItem());
        binding.getHandler().setIndex(getExtraIndex());
        binding.executePendingBindings();

        getWindow().setStatusBarColor(binding.getModel().getColor());
    }

    @Override
    protected void onResume() {
        super.onResume();
        registerReceiver(dynamicReceiver, dynamicFilter);
        registerReceiver(widgetProvider, widgetFilter);
    }

    @Override
    protected void onPause() {
        super.onPause();
        unregisterReceiver(dynamicReceiver);
        unregisterReceiver(widgetProvider);
    }

    public static void startActivity(Context context, FoodItem item, int index) {
        Intent intent = new Intent(context, FoodDetailActivity.class);
        intent.putExtra("food", item);
        intent.putExtra("index", index);
        context.startActivity(intent);
    }

    private FoodItem getExtraFoodItem() {
        return getIntent().getParcelableExtra("food");
    }

    private int getExtraIndex() {
        return getIntent().getIntExtra("index", -1);
    }
}
