package com.icytown.course.experimentone.context;

import android.arch.lifecycle.ViewModelProviders;
import android.content.Context;
import android.content.Intent;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import com.icytown.course.experimentone.R;
import com.icytown.course.experimentone.databinding.ActivityFoodListBinding;
import com.icytown.course.experimentone.factory.ViewModelFactory;
import com.icytown.course.experimentone.handler.FoodListHandler;
import com.icytown.course.experimentone.model.FoodItem;
import com.icytown.course.experimentone.repository.FoodListRepository;
import com.icytown.course.experimentone.viewmodel.FoodListViewModel;

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
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        switch (requestCode) {
            case REQUESTCODE_RECYCLERVIEW:
            case REQUESTCODE_LISTVIEW:
                if (data != null) {
                    FoodItem item = data.getParcelableExtra("food");
                    int index = data.getIntExtra("index", -1);
                    binding.getHandler().updateFoodList(item, index);
                }
                break;
        }
    }

    public ActivityFoodListBinding getBinding() {
        return binding;
    }

    public static void startActivity(Context context) {
        Intent intent = new Intent(context, FoodListActivity.class);
        context.startActivity(intent);
    }
}
