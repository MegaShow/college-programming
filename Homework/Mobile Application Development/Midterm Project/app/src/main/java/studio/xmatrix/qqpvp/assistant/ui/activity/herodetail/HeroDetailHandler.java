package studio.xmatrix.qqpvp.assistant.ui.activity.herodetail;

import android.arch.lifecycle.ViewModelProvider;
import android.arch.lifecycle.ViewModelProviders;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.Typeface;
import android.net.Uri;
import android.os.Handler;
import android.support.v4.app.Fragment;
import android.support.v7.app.ActionBar;
import android.support.v7.widget.LinearLayoutManager;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;
import java.util.Objects;

import javax.inject.Inject;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.data.model.CollectionItem;
import studio.xmatrix.qqpvp.assistant.data.model.HeroDetailItem;
import studio.xmatrix.qqpvp.assistant.databinding.DetailActivityBinding;
import studio.xmatrix.qqpvp.assistant.inject.AppInjector;
import studio.xmatrix.qqpvp.assistant.inject.Injectable;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;
import studio.xmatrix.qqpvp.assistant.ui.fragment.card.CardHandler;
import studio.xmatrix.qqpvp.assistant.ui.fragment.detail.DetailFragmentAdapter;
import studio.xmatrix.qqpvp.assistant.ui.fragment.detail.EquipmentFragment;
import studio.xmatrix.qqpvp.assistant.ui.fragment.detail.IntroductionFragment;
import studio.xmatrix.qqpvp.assistant.ui.fragment.detail.SkillFragment;

public class HeroDetailHandler implements Injectable {
    private DetailActivityBinding binding;
    private HeroDetailActivity activity;
    private ViewModel viewModel;
    private MenuItem menuItemLove;
    private MenuItem menuItemShare;
    private String[] skinNameList;
    private int Id;
    @Inject
    ViewModelProvider.Factory viewModelFactory;

    HeroDetailHandler(HeroDetailActivity activity, DetailActivityBinding binding) {
        AppInjector.inject(this);
        this.binding = binding;
        this.activity = activity;
        this.viewModel = ViewModelProviders.of(activity, viewModelFactory).get(ViewModel.class);
    }

    void initData(int heroId) {
        this.Id = heroId;
        this.viewModel.setHeroDetailId(heroId);
        this.viewModel.getHeroDetail().observe(activity, resource -> {
            if (resource == null || resource.data == null) return;
            switch (resource.status) {
                case SUCCESS:
                    initView(resource.data);
                    break;
            }
        });
    }

    // 根据数据初始化界面
    private void initView(HeroDetailItem item) {
        // 标题
        this.binding.detailCollapsingToolbar.setExpandedTitleColor(Color.parseColor("#333333"));
        this.binding.detailCollapsingToolbar.setExpandedTitleTypeface(Typeface.DEFAULT_BOLD);
        this.binding.detailCollapsingToolbar.setTitle(item.getName());
        this.binding.detailToolbar.setNavigationOnClickListener(v -> this.goBack());
        // 设置导航栏
        activity.setSupportActionBar(binding.detailToolbar);
        binding.detailToolbar.setNavigationOnClickListener(v -> this.goBack());
        ActionBar actionBar = activity.getSupportActionBar();
        // 显示返回按钮
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
            actionBar.setDisplayShowHomeEnabled(true);
        }
        // 界面菜单隐藏
        binding.detailAppbar.addOnOffsetChangedListener((appBarLayout, verticalOffset) -> {
            if (Math.abs(verticalOffset) == appBarLayout.getTotalScrollRange()) {
                if (menuItemLove != null) menuItemLove.setVisible(true);
                if (menuItemShare != null) menuItemShare.setVisible(false);
                // Collapsed (make button visible and fab invisible)
            } else if (verticalOffset == 0) {
                binding.detailToolbar.showOverflowMenu();
                if (menuItemLove != null) menuItemLove.setVisible(false);
                if (menuItemShare != null) menuItemShare.setVisible(true);
                // Expanded (make fab visible and toolbar button invisible)
            } else {
                if (menuItemLove != null) menuItemLove.setVisible(false);
                if (menuItemShare != null) menuItemShare.setVisible(false);
                // Somewhere in between
            }
        });
        // 皮肤选择
        SkinAdapter skinAdapter = new SkinAdapter(activity, viewModel);
        String skins = item.getSkins();
        skinNameList = skins.split("\\|");
        List<Integer> skinItemList = new ArrayList<>();
        for (int i = 0; i < skinNameList.length; i++) {
            skinItemList.add(i);
        }
        if (skinNameList.length < 3) {
            binding.detailSkinMore.setVisibility(View.GONE);
        }
        skinAdapter.refreshData(skinItemList);
        skinAdapter.setListener(((index, pos) -> this.setSkin(index)));
        this.setSkin(0);
        this.binding.detailSkinList.setAdapter(skinAdapter);
        LinearLayoutManager layoutManager = new LinearLayoutManager(activity);
        layoutManager.setOrientation(LinearLayoutManager.HORIZONTAL);
        this.binding.detailSkinList.setLayoutManager(layoutManager);
        // 分类
        switch (item.getType()) {
            case "坦克":
                this.binding.detailTopSort.setImageResource(R.mipmap.hero_sort_01);
                break;
            case "战士":
                this.binding.detailTopSort.setImageResource(R.mipmap.hero_sort_03);
                break;
            case "刺客":
                this.binding.detailTopSort.setImageResource(R.mipmap.hero_sort_05);
                break;
            case "法师":
                this.binding.detailTopSort.setImageResource(R.mipmap.hero_sort_02);
                break;
            case "射手":
                this.binding.detailTopSort.setImageResource(R.mipmap.hero_sort_06);
                break;
            case "辅助":
                this.binding.detailTopSort.setImageResource(R.mipmap.hero_sort_04);
                break;
            default:
                this.binding.detailTopSort.setImageResource(R.mipmap.hero_sort_01);
        }

        ArrayList<String> tabList = new ArrayList<>();
        tabList.add("资料");
        tabList.add("技能");
        tabList.add("出装");

        ArrayList<Fragment> fragmentList = new ArrayList<>();
        fragmentList.add(new IntroductionFragment(activity, viewModel, item));
        fragmentList.add(new SkillFragment(activity, viewModel, item));
        fragmentList.add(new EquipmentFragment(activity, viewModel, item));

        this.binding.viewPager.setAdapter(new DetailFragmentAdapter(activity.getSupportFragmentManager(), fragmentList, tabList));

        this.binding.tabLayout.setupWithViewPager(this.binding.viewPager);
    }

    private void setSkin(int index) {
        if (index >= skinNameList.length) return;
        this.binding.detailSkinLoading.setVisibility(View.VISIBLE);
        this.binding.detailTopTitle.setText(skinNameList[index]);
        this.viewModel.getHeroSkinPicture(index).observe(activity, resource -> {
            if (resource == null || resource.data == null) return;
            switch (resource.status) {
                case SUCCESS:
                    this.binding.bgSkin.setImageBitmap(resource.data);
                    this.binding.detailSkinLoading.setVisibility(View.GONE);
                    binding.loadingLayout.setVisibility(View.GONE);
                    (new Handler()).postDelayed(() -> {
                        int width = this.binding.bgSkin.getWidth() / 2 - 300;
                        if (width < 0) width = 0;
                        this.binding.skinScroll.smoothScrollTo(width, 0);
                    }, 200);
                    break;
                case ERROR:
                    activity.finish();
                    Toast.makeText(activity, "似乎遇到了一些麻烦", Toast.LENGTH_SHORT).show();
                    break;
            }
        });
    }

    private boolean goBack() {
        activity.finish();
        return true;
    }

    void setMenuItemLove(MenuItem menuItem) {
        this.menuItemLove = menuItem;
        this.menuItemLove.setOnMenuItemClickListener((item) -> {
            this.onClickLove(null);
            return true;
        });
        // 收藏状态
        if (viewModel.isExistCollection(this.Id)) {
            this.menuItemLove.setIcon(activity.getDrawable(R.drawable.ic_love_red));
        } else {
            this.menuItemLove.setIcon(activity.getDrawable(R.drawable.ic_love_white));
        }
    }

    void setMenuItemShare(MenuItem menuItem) {
        this.menuItemShare = menuItem;
        this.menuItemShare.setOnMenuItemClickListener((item) -> {
            Uri uri = CardHandler.createShareFile(activity.getWindow().getDecorView().getRootView(), activity);
            Intent intent = new Intent(Intent.ACTION_SEND);
            if (uri == null) {
                intent.setType("text/plain");
                String url = String.format(Locale.getDefault(), "http://pvp.qq.com/web201605/herodetail/%d.shtml", Id);
                String text = "向你推荐王者荣耀英雄【" + binding.detailCollapsingToolbar.getTitle() + "】，详见：" + url;
                intent.putExtra(Intent.EXTRA_TEXT, text);
                activity.startActivity(Intent.createChooser(intent, "分享"));
            } else {
                intent.setType("image/*");
                intent.putExtra(Intent.EXTRA_STREAM, uri);
                activity.startActivity(Intent.createChooser(intent, "分享"));
            }
            return true;
        });
    }

    public void onClickLove(View v) {
        if (viewModel.isExistCollection(this.Id)) {
            menuItemLove.setIcon(activity.getDrawable(R.drawable.ic_love_white));
            viewModel.removeCollection(this.Id);
        } else {
            menuItemLove.setIcon(activity.getDrawable(R.drawable.ic_love_red));
            viewModel.addCollection(new CollectionItem(this.Id, CollectionItem.Type.Hero, "", new Date()));
        }
    }

    public void onClickMore(View v) {
        binding.detailAppbar.setExpanded(false);
    }

    public void onClickMoreSkin(View v) {
        binding.detailSkinList.scrollToPosition(Objects.requireNonNull(binding.detailSkinList.getAdapter()).getItemCount() - 1);
    }
}
