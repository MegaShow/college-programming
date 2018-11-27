package studio.xmatrix.qqpvp.assistant.ui.activity.collection;

import android.arch.lifecycle.ViewModelProvider;
import android.arch.lifecycle.ViewModelProviders;
import android.graphics.Color;
import android.support.v7.app.ActionBar;
import android.support.v7.widget.LinearLayoutManager;
import android.view.View;

import javax.inject.Inject;

import jp.wasabeef.recyclerview.adapters.SlideInBottomAnimationAdapter;
import jp.wasabeef.recyclerview.animators.SlideInLeftAnimator;
import studio.xmatrix.qqpvp.assistant.databinding.CollectionActivityBinding;
import studio.xmatrix.qqpvp.assistant.inject.AppInjector;
import studio.xmatrix.qqpvp.assistant.inject.Injectable;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;

public class CollectionHandler implements Injectable {
    private CollectionActivityBinding binding;
    private CollectionActivity activity;
    private ViewModel viewModel;

    private CollectionAdapter adapter;

    @Inject
    ViewModelProvider.Factory viewModelFactory;

    CollectionHandler(CollectionActivity activity, CollectionActivityBinding binding) {
        AppInjector.inject(this);
        this.activity =activity;
        this.binding = binding;
        viewModel = ViewModelProviders.of(activity, viewModelFactory).get(ViewModel.class);
        initView();
        initList();
    }

    private void initList() {
        adapter = new CollectionAdapter(activity, viewModel);
        binding.collectRecycler.setItemAnimator(new SlideInLeftAnimator());
        binding.collectRecycler.setAdapter(new SlideInBottomAnimationAdapter(adapter));
        binding.collectRecycler.setLayoutManager(new LinearLayoutManager(activity));

        final boolean[] init = {false};
        viewModel.getCollectionList(activity).observe(activity, resource -> {
            if (resource != null) {
                binding.collectNull.setVisibility(resource.size() != 0 ? View.GONE : View.VISIBLE);
                if (init[0]) {
                    adapter.observeData(resource);
                } else {
                    adapter.refreshData(resource);
                    init[0] = true;
                }
            }
        });
    }

    private void initView() {
        binding.collectCollapsingToolbar.setTitle("收藏");
        // 设置颜色
        binding.collectCollapsingToolbar.setExpandedTitleColor(Color.WHITE);
        binding.collectCollapsingToolbar.setCollapsedTitleTextColor(Color.WHITE);
        // 设置导航栏
        activity.setSupportActionBar(binding.collectToolbar);
        binding.collectToolbar.setNavigationOnClickListener(v -> activity.finish());
        ActionBar actionBar = activity.getSupportActionBar();
        // 显示返回按钮
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
            actionBar.setDisplayShowHomeEnabled(true);
        }
        // 列表动画
        SlideInLeftAnimator slideInLeftAnimator = new SlideInLeftAnimator();
        slideInLeftAnimator.setAddDuration(300);
        binding.collectRecycler.setItemAnimator(slideInLeftAnimator);

    }
}
