package com.icytown.course.experimentone.adapter;

import android.databinding.DataBindingUtil;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.icytown.course.experimentone.BR;
import com.icytown.course.experimentone.R;
import com.icytown.course.experimentone.databinding.ItemFoodBinding;
import com.icytown.course.experimentone.model.FoodItem;
import com.icytown.course.experimentone.presenter.FoodItemPresenter;

import java.util.List;

public class FoodAdapter extends RecyclerView.Adapter<FoodAdapter.BindingHolder> {

    private List<FoodItem> mFoodList;

    public FoodAdapter(List<FoodItem> foodList) {
        mFoodList = foodList;
    }

    @NonNull
    @Override
    public BindingHolder onCreateViewHolder(@NonNull ViewGroup parent, int i) {
        ItemFoodBinding binding = DataBindingUtil.inflate(LayoutInflater.from(parent.getContext()), R.layout.item_food, parent, false);
        binding.setPresenter(new FoodItemPresenter());
        BindingHolder holder = new BindingHolder(binding.getRoot());
        holder.setBinding(binding);
        return holder;
    }

    @Override
    public void onBindViewHolder(@NonNull BindingHolder viewHolder, int i) {
        viewHolder.getBinding().setVariable(BR.model, mFoodList.get(i));
        viewHolder.getBinding().executePendingBindings();
    }

    @Override
    public int getItemCount() {
        return mFoodList.size();
    }

    static class BindingHolder extends RecyclerView.ViewHolder {

        private ItemFoodBinding binding;

        BindingHolder(@NonNull View itemView) {
            super(itemView);
        }

        public ItemFoodBinding getBinding() {
            return binding;
        }

        public void setBinding(ItemFoodBinding binding) {
            this.binding = binding;
        }
    }
}
