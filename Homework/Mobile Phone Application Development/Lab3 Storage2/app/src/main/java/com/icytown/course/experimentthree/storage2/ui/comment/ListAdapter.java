package com.icytown.course.experimentthree.storage2.ui.comment;

import android.content.Context;
import android.databinding.BindingAdapter;
import android.databinding.DataBindingUtil;
import android.graphics.Bitmap;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.SparseBooleanArray;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;

import com.icytown.course.experimentthree.storage2.R;
import com.icytown.course.experimentthree.storage2.data.model.Item;
import com.icytown.course.experimentthree.storage2.databinding.CommentItemBinding;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;
import java.util.Locale;

public class ListAdapter extends ArrayAdapter<Item> {

    private List<Item> data;

    public ListAdapter(@NonNull Context context, int resource, @NonNull List<Item> objects) {
        super(context, resource, objects);
        data = objects;
    }

    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        final BindingHolder holder;
        if (convertView == null) {
            holder = new BindingHolder();
            CommentItemBinding binding = DataBindingUtil.inflate(LayoutInflater.from(parent.getContext()), R.layout.comment_item, parent, false);
            binding.setPresenter(new Presenter());
            binding.getRoot().setTag(holder);
            holder.setBinding(binding);
        } else {
            holder = (BindingHolder) convertView.getTag();
        }
        holder.getBinding().setModel(getItem(position));
        holder.getBinding().executePendingBindings();
        return holder.getBinding().getRoot();
    }

    @BindingAdapter({"imageBitmap"})
    public static void loadImage(ImageView iv, Bitmap bitmap) {
        if (bitmap == null) {
            iv.setImageResource(R.mipmap.me);
        } else {
            iv.setImageBitmap(bitmap);
        }
    }

    public static String covertDateToString(Date date) {
        return new SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.getDefault()).format(date);
    }

    class BindingHolder {

        private CommentItemBinding binding;

        CommentItemBinding getBinding() {
            return binding;
        }

        void setBinding(CommentItemBinding binding) {
            this.binding = binding;
        }
    }
}
