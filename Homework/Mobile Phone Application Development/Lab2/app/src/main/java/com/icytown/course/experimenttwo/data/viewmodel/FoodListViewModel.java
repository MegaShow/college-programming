package com.icytown.course.experimenttwo.data.viewmodel;

import android.arch.lifecycle.LiveData;
import android.arch.lifecycle.MutableLiveData;
import android.arch.lifecycle.ViewModel;

import com.icytown.course.experimenttwo.data.model.FoodItem;
import com.icytown.course.experimenttwo.data.repository.FoodListRepository;
import com.icytown.course.experimenttwo.presentation.foodlist.FoodAdapter;
import com.icytown.course.experimenttwo.presentation.foodlist.FoodCollectionAdapter;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class FoodListViewModel extends ViewModel {

    private LiveData<List<FoodItem>> data;
    private LiveData<List<FoodItem>> collectData;
    private FoodListRepository repository;
    private FoodAdapter adapter;
    private FoodCollectionAdapter collectAdapter;

    public FoodListViewModel(FoodListRepository repository) {
        this.repository = repository;
    }

    public List<FoodItem> getData() {
        if (data == null) {
            loadData();
        }
        return data.getValue();
    }

    public List<FoodItem> getCollectData() {
        if (collectData == null) {
            loadCollectData();
        }
        return collectData.getValue();
    }

    public FoodAdapter getAdapter() {
        return adapter;
    }

    public void setAdapter(FoodAdapter adapter) {
        this.adapter = adapter;
    }

    public FoodCollectionAdapter getCollectAdapter() {
        return collectAdapter;
    }

    public void setCollectAdapter(FoodCollectionAdapter collectAdapter) {
        this.collectAdapter = collectAdapter;
    }

    public void updateItem(FoodItem item, int index) {
        FoodItem old = getData().get(index);
        if (old.isStar() != item.isStar()) {
            old.setStar(item.isStar());
        }
        if (old.isCollect() != item.isCollect()) {
            old.setCollect(item.isCollect());
            if (old.isCollect()) {
                getCollectData().add(old);
            } else {
                getCollectData().remove(old);
            }
            collectAdapter.notifyDataSetChanged();
        }
    }

    public boolean removeItem(FoodItem item) {
        boolean flag = false;
        if (getData().remove(item)) {
            flag = true;
            adapter.notifyDataSetChanged();
        }
        if (getCollectData().remove(item)) {
            collectAdapter.notifyDataSetChanged();
        }
        return flag;
    }

    public boolean removeCollectItem(FoodItem item) {
        if (getCollectData().remove(item)) {
            item.setCollect(false);
            collectAdapter.notifyDataSetChanged();
            return true;
        }
        return false;
    }

    private void loadCollectData() {
        if (data == null) {
            loadData();
        }
        collectData = new MutableLiveData<>();
        final List<FoodItem> list = new ArrayList<>();
        list.add(new FoodItem("收藏夹", "*"));
        for (FoodItem item : Objects.requireNonNull(data.getValue())) {
            if (item.isCollect()) {
                list.add(item);
            }
        }
        ((MutableLiveData<List<FoodItem>>) collectData).setValue(list);
    }

    private void loadData() {
        data = repository.getFoodList();
    }
}
