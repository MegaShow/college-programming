package com.icytown.course.experimenttwo.presentation.foodlist;

import android.content.Context;
import android.databinding.DataBindingUtil;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;

import com.icytown.course.experimenttwo.R;
import com.icytown.course.experimenttwo.data.model.FoodItem;
import com.icytown.course.experimenttwo.databinding.ItemFoodBinding;

import java.util.List;

public class FoodCollectionAdapter extends ArrayAdapter<FoodItem> {

    public FoodCollectionAdapter(@NonNull Context context, int resource, @NonNull List<FoodItem> objects) {
        super(context, resource, objects);
    }

    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        final BindingHolder holder;
        if (convertView == null) {
            holder = new BindingHolder();
            ItemFoodBinding binding = DataBindingUtil.inflate(LayoutInflater.from(parent.getContext()), R.layout.item_food, parent, false);
            binding.setPresenter(new FoodCollectionItemPresenter());
            binding.getRoot().setTag(holder);
            holder.setBinding(binding);
        } else {
            holder = (BindingHolder) convertView.getTag();
        }
        holder.getBinding().setModel(getItem(position));
        holder.getBinding().executePendingBindings();
        return holder.getBinding().getRoot();
    }

    class BindingHolder {

        private ItemFoodBinding binding;

        public ItemFoodBinding getBinding() {
            return binding;
        }

        public void setBinding(ItemFoodBinding binding) {
            this.binding = binding;
        }
    }
}
