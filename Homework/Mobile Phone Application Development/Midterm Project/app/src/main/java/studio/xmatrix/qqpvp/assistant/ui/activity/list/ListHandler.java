package studio.xmatrix.qqpvp.assistant.ui.activity.list;

import android.arch.lifecycle.ViewModelProvider;
import android.arch.lifecycle.ViewModelProviders;
import android.graphics.Color;
import android.support.v7.app.ActionBar;
import android.view.MenuItem;
import android.view.View;

import com.scwang.smartrefresh.header.DeliveryHeader;

import javax.inject.Inject;

import jp.wasabeef.recyclerview.animators.SlideInLeftAnimator;
import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.databinding.ListActivityBinding;
import studio.xmatrix.qqpvp.assistant.inject.AppInjector;
import studio.xmatrix.qqpvp.assistant.inject.Injectable;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;

public class ListHandler implements Injectable {

    private ListActivity activity;
    private ListActivityBinding binding;
    private MenuItem menuItem;
    private int type;
    private ListTypeHandler typeHandler;

    @Inject
    ViewModelProvider.Factory viewModelFactory;

    ListHandler(ListActivity activity, ListActivityBinding binding, int type) {
        AppInjector.inject(this);
        this.activity = activity;
        this.binding = binding;
        this.type = type;
        ViewModel viewModel = ViewModelProviders.of(activity, viewModelFactory).get(ViewModel.class);
        if (type == 1) {
            this.typeHandler = new ListItemHandler(activity, binding, viewModel);
        } else if (type == 2) {
            this.typeHandler = new ListSkillHandler(activity, binding, viewModel);
        } else {
            this.typeHandler = new ListHeroHandler(activity, binding, viewModel);
        }
        typeHandler.initList();
        initView();
    }

    private void initView() {
        // 设置颜色
        binding.listCollapsingToolbar.setExpandedTitleColor(activity.getColor(R.color.colorText));
        binding.listCollapsingToolbar.setCollapsedTitleTextColor(Color.WHITE);
        // 设置导航栏
        activity.setSupportActionBar(binding.listToolbar);
        binding.listToolbar.setNavigationOnClickListener(v -> this.goBack());
        ActionBar actionBar = activity.getSupportActionBar();
        // 显示返回按钮
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
            actionBar.setDisplayShowHomeEnabled(true);
        }
        // 界面菜单隐藏
        binding.listAppbar.addOnOffsetChangedListener((appBarLayout, verticalOffset) -> {
            if (Math.abs(verticalOffset) == appBarLayout.getTotalScrollRange()) {
                if (menuItem != null) menuItem.setVisible(true);
                // Collapsed (make button visible and fab invisible)
            } else if (verticalOffset == 0) {
                binding.listToolbar.showOverflowMenu();
                if (menuItem != null) menuItem.setVisible(false);
                // Expanded (make fab visible and toolbar button invisible)
            } else {
                if (menuItem != null) menuItem.setVisible(false);
                // Somewhere in between
            }
        });
        // 列表动画
        SlideInLeftAnimator slideInLeftAnimator = new SlideInLeftAnimator();
        slideInLeftAnimator.setAddDuration(300);
        binding.listRecycler.setItemAnimator(slideInLeftAnimator);
        // 下拉刷新
        binding.refreshLayout.setOnRefreshListener(refreshLayout -> typeHandler.onRefresh(refreshLayout));
        // ClassicsHeader classicsHeader = new ClassicsHeader(activity);
        // 设置上次刷新时间
        // Date lastUpdate = new Date();
        // lastUpdate.setTime(new Date().getTime() - 100000);
        // classicsHeader.setLastUpdateTime(lastUpdate);
        binding.refreshLayout.setRefreshHeader(new DeliveryHeader(activity));
        // 初始化页面
        typeHandler.initView();
    }

    void setMenuItem(MenuItem menuItem) {
        if (this.type != 2) {
            this.menuItem = menuItem;
            this.menuItem.setOnMenuItemClickListener((item) -> {
                this.onClickFilter(null);
                return true;
            });
        }
    }

    private boolean goBack() {
        activity.finish();
        return true;
    }

    public void onClickFilter(View v) {
        this.typeHandler.onClickFilter();
    }

}
