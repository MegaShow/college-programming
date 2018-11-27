package studio.xmatrix.qqpvp.assistant.ui.activity.search;

import android.annotation.SuppressLint;
import android.arch.lifecycle.ViewModelProvider;
import android.arch.lifecycle.ViewModelProviders;
import android.support.v7.app.ActionBar;
import android.support.v7.widget.LinearLayoutManager;
import android.view.View;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import javax.inject.Inject;

import jp.wasabeef.recyclerview.adapters.SlideInBottomAnimationAdapter;
import jp.wasabeef.recyclerview.animators.SlideInLeftAnimator;
import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.data.common.Resource;
import studio.xmatrix.qqpvp.assistant.data.model.HeroListItem;
import studio.xmatrix.qqpvp.assistant.data.model.ItemItem;
import studio.xmatrix.qqpvp.assistant.data.model.SearchItem;
import studio.xmatrix.qqpvp.assistant.data.model.SummonerItem;
import studio.xmatrix.qqpvp.assistant.databinding.SearchActivityBinding;
import studio.xmatrix.qqpvp.assistant.inject.AppInjector;
import studio.xmatrix.qqpvp.assistant.inject.Injectable;
import studio.xmatrix.qqpvp.assistant.ui.activity.herodetail.HeroDetailActivity;
import studio.xmatrix.qqpvp.assistant.ui.activity.list.ListItemHandler;
import studio.xmatrix.qqpvp.assistant.ui.activity.list.ListSkillHandler;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;

public class SearchHandler implements Injectable, SearchListAdapter.OnItemClickListener {
    private SearchActivityBinding binding;
    private SearchActivity activity;
    private ViewModel viewModel;
    private List<String> searchSuggest;
    private List<SearchItem> searchItems;
    private SearchListAdapter adapter;

    @Inject
    ViewModelProvider.Factory viewModelFactory;

    SearchHandler(SearchActivity activity, SearchActivityBinding binding) {
        AppInjector.inject(this);
        this.binding = binding;
        this.activity = activity;
        this.searchSuggest = new ArrayList<>();
        this.searchItems = new ArrayList<>();
        viewModel = ViewModelProviders.of(activity, viewModelFactory).get(ViewModel.class);
        initView();
        viewModel.getHeroList().observe(activity, (res) -> {
            if (res != null) {
                switch (res.status) {
                    case SUCCESS:
                        for (HeroListItem item : Objects.requireNonNull(res.data)) {
                            this.searchSuggest.add("1" + item.getName());
                            searchItems.add(new SearchItem(item.getId(), item.getName(), item.getTypes() +" · "+ item.getDefaultSkin(), SearchItem.ItemType.HERO));
                        }
                        setSearchSuggest();
                        break;
                    case ERROR:
                        break;
                }
            }
        });
        viewModel.getSummonerList().observe(activity, (res) -> {
            if (res != null) {
                switch (res.status) {
                    case SUCCESS:
                        for (SummonerItem item : Objects.requireNonNull(res.data)) {
                            this.searchSuggest.add("2" + item.getName());
                            searchItems.add(new SearchItem(item.getId(), item.getName(), item.getRank(), SearchItem.ItemType.SKILL));
                        }
                        setSearchSuggest();
                        break;
                    case ERROR:
                        break;
                }
            }
        });
        viewModel.getNormalItemList().observe(activity, (res) -> {
            if (res != null) {
                switch (res.status) {
                    case SUCCESS:
                        for (ItemItem item : Objects.requireNonNull(res.data)) {
                            this.searchSuggest.add("3" + item.getName());
                            searchItems.add(new SearchItem(item.getId(), item.getName(), "常规装备", SearchItem.ItemType.ITEM));
                        }
                        setSearchSuggest();
                        break;
                    case ERROR:
                        break;
                }
            }
        });
        viewModel.getSpecialItemList().observe(activity, (res) -> {
            if (res != null) {
                switch (res.status) {
                    case SUCCESS:
                        for (ItemItem item : Objects.requireNonNull(res.data)) {
                            this.searchSuggest.add("4" + item.getName());
                            searchItems.add(new SearchItem(item.getId(), item.getName(), "边境突围装备", SearchItem.ItemType.SPITEM));
                        }
                        setSearchSuggest();
                        break;
                    case ERROR:
                        break;
                }
            }
        });
    }

    private void setSearchSuggest() {
        this.binding.searchView.setSuggestions(this.searchSuggest.toArray(new String[0]));
    }

    private void initView() {
        // 标题框
        activity.setSupportActionBar(binding.searchToolbar);
        ActionBar actionBar = activity.getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
            actionBar.setTitle(null);
        }
        // 搜索框
        SearchListener searchListener = new SearchListener();
        binding.searchView.setAdapter(new SearchAdapter(activity, new String[0]));
        binding.searchView.setOnQueryTextListener(searchListener);
        binding.searchView.setOnSearchViewListener(searchListener);
        binding.searchView.setVoiceSearch(false);
        binding.searchView.setHint(activity.getResources().getString(R.string.menu_hint_search));
        setSearchSuggest();
        // 提示图标
        binding.searchResultLayout.setOnClickListener(this::onClickHeader);
        // 返回按钮
        binding.searchToolbar.setNavigationOnClickListener((v) -> activity.finish());
        // 点击标题
        binding.searchTitle.setOnClickListener(this::onClickHeader);
        // 列表
        adapter = new SearchListAdapter(activity, viewModel);
        adapter.setListener(this);
        binding.searchResultList.setItemAnimator(new SlideInLeftAnimator());
        binding.searchResultList.setAdapter(new SlideInBottomAnimationAdapter(adapter));
        binding.searchResultList.setLayoutManager(new LinearLayoutManager(activity));
    }

    public void onClickHeader(View v) {
        binding.searchResultLayout.setVisibility(View.GONE);
        binding.searchView.showSearch();
    }

    @Override
    public void onItemClick(SearchItem item, int pos) {
        switch (item.getType()) {
            case HERO:
                HeroDetailActivity.startActivity(activity, item.getId());
                break;
            case ITEM:
                viewModel.getNormalItemList().observe(activity, res -> {
                    if (res != null && res.data != null && res.status == Resource.Status.SUCCESS) {
                        for (ItemItem i : res.data) {
                            if (i.getId() == item.getId()) {
                                ListItemHandler.showCard(activity, viewModel, i, true);
                                break;
                            }
                        }
                    }
                });
                break;
            case SKILL:
                viewModel.getSummonerList().observe(activity, res -> {
                    if (res != null && res.data != null && res.status == Resource.Status.SUCCESS) {
                        for (SummonerItem i : res.data) {
                            if (i.getId() == item.getId()) {
                                ListSkillHandler.showCard(activity, viewModel, i);
                                break;
                            }
                        }
                    }
                });
                break;
            case SPITEM:
                viewModel.getSpecialItemList().observe(activity, res -> {
                    if (res != null && res.data != null && res.status == Resource.Status.SUCCESS) {
                        for (ItemItem i : res.data) {
                            if (i.getId() == item.getId()) {
                                ListItemHandler.showCard(activity, viewModel, i, false);
                                break;
                            }
                        }
                    }
                });
                break;
        }
    }

    private class SearchListener implements MaterialSearchView.OnQueryTextListener, MaterialSearchView.SearchViewListener {
        @SuppressLint("SetTextI18n")
        @Override
        public boolean onQueryTextSubmit(String query) {
            List<SearchItem> res = new ArrayList<>();
            for (SearchItem item : searchItems) {
                if (item.getName().contains(query)) {
                    res.add(item);
                }
            }
            adapter.refreshData(res);
            binding.searchTitle.setText("搜索：" + query);
            if (res.size() == 0) {
                binding.searchResultText.setText("咦，居然找不到😂");
                binding.searchResultLayout.setVisibility(View.VISIBLE);
                binding.searchResultList.setVisibility(View.GONE);
            } else {
                binding.searchResultLayout.setVisibility(View.GONE);
                binding.searchResultList.setVisibility(View.VISIBLE);
            }
            return false;
        }

        @Override
        public boolean onQueryTextChange(String newText) {

            return false;
        }

        @Override
        public void onSearchViewShown() {
            binding.searchResultLayout.setVisibility(View.GONE);
        }

        @Override
        public void onSearchViewClosed() {
            if (adapter.getItemCount() == 0)
                binding.searchResultLayout.setVisibility(View.VISIBLE);
        }
    }
}
