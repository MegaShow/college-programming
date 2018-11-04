package com.icytown.course.experimenttwo.presentation.foodlist;

import android.arch.lifecycle.ViewModelProviders;
import android.content.Context;
import android.content.Intent;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import com.icytown.course.experimenttwo.R;
import com.icytown.course.experimenttwo.data.model.FoodItem;
import com.icytown.course.experimenttwo.data.repository.FoodListRepository;
import com.icytown.course.experimenttwo.data.viewmodel.FoodListViewModel;
import com.icytown.course.experimenttwo.data.viewmodel.ViewModelFactory;
import com.icytown.course.experimenttwo.databinding.ActivityFoodListBinding;

import org.greenrobot.eventbus.EventBus;

public class FoodListActivity extends AppCompatActivity {

    public static final int REQUESTCODE_RECYCLERVIEW = 1;
    public static final int REQUESTCODE_LISTVIEW = 2;

    private ActivityFoodListBinding binding;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = DataBindingUtil.setContentView(this, R.layout.activity_food_list);
        ViewModelFactory factory = new ViewModelFactory(new FoodListRepository(this));
        FoodListViewModel viewModel = ViewModelProviders.of(this, factory).get(FoodListViewModel.class);
        binding.setHandler(new FoodListHandler(this, binding, viewModel));

        EventBus.getDefault().register(binding.getHandler());

        FoodItem item = getIntent().getParcelableExtra("food");
        int index = getIntent().getIntExtra("index", -1);
        if (item != null) {
            binding.getHandler().updateFoodList(item, index);
            binding.getHandler().showCollection(true);
        }
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        setIntent(intent);
        if (getIntent().getParcelableExtra("food") != null) {
            binding.getHandler().showCollection(true);
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        EventBus.getDefault().unregister(binding.getHandler());
    }

    public ActivityFoodListBinding getBinding() {
        return binding;
    }

    public static void startActivity(Context context) {
        Intent intent = new Intent(context, FoodListActivity.class);
        context.startActivity(intent);
    }
}
