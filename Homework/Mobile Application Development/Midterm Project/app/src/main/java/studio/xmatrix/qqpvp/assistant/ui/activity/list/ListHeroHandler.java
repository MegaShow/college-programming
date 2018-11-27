package studio.xmatrix.qqpvp.assistant.ui.activity.list;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.PorterDuff;
import android.os.Handler;
import android.support.design.button.MaterialButton;
import android.support.v4.content.ContextCompat;
import android.support.v7.widget.GridLayoutManager;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;

import com.scwang.smartrefresh.layout.api.RefreshLayout;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import jp.wasabeef.recyclerview.adapters.AlphaInAnimationAdapter;
import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.data.common.Resource;
import studio.xmatrix.qqpvp.assistant.data.model.HeroListItem;
import studio.xmatrix.qqpvp.assistant.data.model.ListItem;
import studio.xmatrix.qqpvp.assistant.databinding.HeroSheetFragmentBinding;
import studio.xmatrix.qqpvp.assistant.databinding.ListActivityBinding;
import studio.xmatrix.qqpvp.assistant.receiver.FreeNotification;
import studio.xmatrix.qqpvp.assistant.ui.activity.herodetail.HeroDetailActivity;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;
import studio.xmatrix.qqpvp.assistant.ui.fragment.sheet.HeroSheetFragment;

public class ListHeroHandler implements ListTypeHandler, ListAdapter.OnItemClickListener {
    private ListActivity activity;
    private ListActivityBinding binding;
    private ViewModel viewModel;

    private ListAdapter adapter;
    private HeroSheetFragmentBinding sheetBinding;
    private HeroSheetFragment sheet;
    private int sort;

    ListHeroHandler(ListActivity activity, ListActivityBinding binding, ViewModel viewModel) {
        this.activity = activity;
        this.binding = binding;
        this.viewModel = viewModel;
        this.sort = R.id.sheet_btn_all;
    }

    public void initView() {
        binding.listCollapsingToolbar.setTitle("英雄");
        binding.listTopImg.setImageResource(R.mipmap.list_hero_bg);
    }

    public void initList() {
        setAdapter();
        viewModel.getHeroList().observe(activity, resource -> {
            if (resource != null) {
                switch (resource.status) {
                    case LOADING:
                        binding.loadingProgressbar.setVisibility(View.VISIBLE);
                        binding.listNetworkError.setVisibility(View.GONE);
                        break;
                    case ERROR:
                        if (resource.data == null || resource.data.size() == 0) {
                            binding.loadingProgressbar.setVisibility(View.GONE);
                            binding.listNetworkError.setVisibility(View.VISIBLE);
                            break;
                        }
                    case SUCCESS:
                        binding.listNetworkError.setVisibility(View.GONE);
                        binding.loadingProgressbar.setVisibility(View.GONE);
                        adapter.refreshData(resource.data);
                        Set<String> freehero = new HashSet<>();
                        boolean save = !FreeNotification.isUpdated(activity);
                        if(save) {
                            for (HeroListItem item : resource.data){
                                if(item.isFreeHero()) {
                                    freehero.add(Integer.toString(item.getId()) + "," + item.getName());
                                }
                            }
                            FreeNotification.updateFreeHero(activity, freehero);
                            activity.startService(new Intent(activity, FreeNotification.class));
                        }
                        break;
                }
            }
        });
    }

    private void setAdapter() {
        adapter = new ListAdapter(activity, viewModel, 0);
        adapter.setListener(this);
        binding.listRecycler.setAdapter(new AlphaInAnimationAdapter(adapter));
        binding.listRecycler.setLayoutManager(new GridLayoutManager(activity, 3));
    }

    @Override
    public void onItemClick(ListItem item, int pos) {
        HeroDetailActivity.startActivity(activity, item.getId());
    }

    public void onClickSort(View v) {
        if ((v != null && this.sort == v.getId()) || this.adapter == null) return;
        if (v != null)  this.sort = v.getId();
        final String title;
        switch (this.sort) {
            case R.id.sheet_btn_all:
                title = "英雄";
                break;
            case R.id.sheet_btn_new:
                title = "新手推荐";
                break;
            case R.id.sheet_btn_week:
                title = "本周免费";
                break;
            case R.id.sheet_sort_1:
                title = "坦克";
                break;
            case R.id.sheet_sort_2:
                title = "法师";
                break;
            case R.id.sheet_sort_3:
                title = "战士";
                break;
            case R.id.sheet_sort_4:
                title = "辅助";
                break;
            case R.id.sheet_sort_5:
                title = "刺客";
                break;
            case R.id.sheet_sort_6:
                title = "射手";
                break;
            default:
                title = "英雄";
        }
        viewModel.getHeroList().observe(activity, resource -> {
            if (resource != null && resource.status == Resource.Status.SUCCESS && resource.data != null) {
                List<ListItem> data = new ArrayList<>();
                for (HeroListItem item : resource.data) {
                    if (title.equals("英雄") ||
                            (title.equals("新手推荐") && item.isRecommendHero()) ||
                            (title.equals("本周免费") && item.isFreeHero()) ||
                            item.getTypes().contains(title)) {
                        data.add(item);
                    }
                }
                binding.listCollapsingToolbar.setTitle(title);
                this.adapter.refreshData(data);
                if (this.sheet != null) this.sheet.dismiss();
            }
        });
    }

    @Override
    public void onClickFilter() {
        this.sheet = new HeroSheetFragment((sheetBinding) -> {
            this.sheetBinding = sheetBinding;
            this.sheetBinding.setHandler(this);
            setBtnBackground(this.sort);
            setImageFilter(this.sort);
        });
        this.sheet.show(activity.getSupportFragmentManager(), "BottomSort");
    }

    @Override
    public void onRefresh(RefreshLayout refreshLayout) {
        viewModel.getHeroListForcibly(activity).observe(activity, res -> {
            if (res != null && res.data != null) {
                switch (res.status) {
                    case SUCCESS:
                        binding.listNetworkError.setVisibility(View.GONE);
                        onClickSort(null);
                        refreshLayout.finishRefresh(true);
                        break;
                    case ERROR:
                        refreshLayout.finishRefresh(false);
                        break;
                }
            }
        });
    }

    private void setBtnBackground(int sort) {
        MaterialButton buttons[] = {this.sheetBinding.sheetBtnAll, this.sheetBinding.sheetBtnNew, this.sheetBinding.sheetBtnWeek};
        for (MaterialButton button : buttons) {
            if (sort == button.getId()) {
                button.setBackgroundTintList(ContextCompat.getColorStateList(activity, R.color.colorPrimaryDark));
            } else {
                button.setBackgroundTintList(ContextCompat.getColorStateList(activity, R.color.colorBtnGray));
            }
        }
    }

    private void setImageFilter(int sort) {
        ImageView images[] = {sheetBinding.sheetSort1, sheetBinding.sheetSort2, sheetBinding.sheetSort3,
                sheetBinding.sheetSort4, sheetBinding.sheetSort5, sheetBinding.sheetSort6};
        for (ImageView image : images) {
            if (sort == image.getId()) {
                image.setColorFilter(activity.getColor(R.color.colorPrimaryDark), PorterDuff.Mode.SRC_ATOP);
            } else {
                image.clearColorFilter();
            }
        }
    }

}
