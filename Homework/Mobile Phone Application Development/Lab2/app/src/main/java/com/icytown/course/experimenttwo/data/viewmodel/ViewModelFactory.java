package com.icytown.course.experimenttwo.data.viewmodel;

import android.arch.lifecycle.ViewModel;
import android.arch.lifecycle.ViewModelProvider;

import com.icytown.course.experimenttwo.data.repository.FoodListRepository;

public class ViewModelFactory extends ViewModelProvider.NewInstanceFactory {

    private FoodListRepository repository;

    public ViewModelFactory(FoodListRepository repository) {
        this.repository = repository;
    }

    @Override
    public <T extends ViewModel> T create(Class<T> modelClass) {
        return (T) new FoodListViewModel(repository);
    }
}
