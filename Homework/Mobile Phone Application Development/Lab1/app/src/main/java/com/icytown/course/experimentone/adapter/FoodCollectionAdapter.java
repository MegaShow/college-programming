package com.icytown.course.experimentone.adapter;

import android.content.Context;
import android.databinding.DataBindingUtil;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;

import com.icytown.course.experimentone.R;
import com.icytown.course.experimentone.databinding.ItemFoodBinding;
import com.icytown.course.experimentone.model.FoodItem;
import com.icytown.course.experimentone.presenter.FoodCollectionItemPresenter;

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
