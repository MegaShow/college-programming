package studio.xmatrix.qqpvp.assistant.ui.activity.list;

import android.annotation.SuppressLint;
import android.os.Handler;
import android.support.design.button.MaterialButton;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.GridLayoutManager;
import android.view.View;
import android.widget.Toast;

import com.scwang.smartrefresh.layout.api.RefreshLayout;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import jp.wasabeef.recyclerview.adapters.AlphaInAnimationAdapter;
import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.data.common.Resource;
import studio.xmatrix.qqpvp.assistant.data.model.CollectionItem;
import studio.xmatrix.qqpvp.assistant.data.model.ItemItem;
import studio.xmatrix.qqpvp.assistant.data.model.ListItem;
import studio.xmatrix.qqpvp.assistant.databinding.ItemCardBinding;
import studio.xmatrix.qqpvp.assistant.databinding.ItemSheetFragmentBinding;
import studio.xmatrix.qqpvp.assistant.databinding.ListActivityBinding;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;
import studio.xmatrix.qqpvp.assistant.ui.fragment.card.CardFragment;
import studio.xmatrix.qqpvp.assistant.ui.fragment.sheet.ItemSheetFragment;

public class ListItemHandler implements ListTypeHandler, ListAdapter.OnItemClickListener {
    private ListActivity activity;
    private ListActivityBinding binding;
    private ViewModel viewModel;

    private ListAdapter adapter;

    private ItemSheetFragmentBinding sheetBinding;
    private ItemSheetFragment sheet;
    private int sort;
    private int sortClass;

    ListItemHandler(ListActivity activity, ListActivityBinding binding, ViewModel viewModel) {
        this.activity = activity;
        this.binding = binding;
        this.viewModel = viewModel;
        this.sort = R.id.sheet_item_btn_all;
        this.sortClass = 0;
    }

    @Override
    public void initView() {
        binding.listCollapsingToolbar.setTitle("常规装备");
        binding.listTopImg.setImageResource(R.mipmap.list_item_bg);
    }

    @Override
    public void initList() {
        setAdapter();
        viewModel.getNormalItemList().observe(activity, resource -> {
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
                        adapter.addData(resource.data);
                        break;
                }
            }
        });
    }

    @Override
    public void onRefresh(RefreshLayout refreshLayout) {
        if (this.sortClass == 0) {
            viewModel.getNormalItemListForcibly(activity).observe(activity, res -> {
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
        } else {
            viewModel.getSpecialItemListForcibly(activity).observe(activity, res -> {
                if (res != null && res.data != null) {
                    switch (res.status) {
                        case SUCCESS:
                            binding.listNetworkError.setVisibility(View.GONE);
                            onClickSortSp(null);
                            refreshLayout.finishRefresh(true);
                            break;
                        case ERROR:
                            refreshLayout.finishRefresh(false);
                            break;
                    }
                }
            });
        }
    }

    @Override
    public void onClickFilter() {
        this.sheet = new ItemSheetFragment((sheetBinding) -> {
            this.sheetBinding = sheetBinding;
            this.sheetBinding.setHandler(this);
            setSortClassView(this.sortClass);
            setBtnBackgroundTint(this.sort);
        });
        this.sheet.show(activity.getSupportFragmentManager(), "ItemBottomSort");
    }

    private void setAdapter() {
        adapter = new ListAdapter(activity, viewModel, 1);
        adapter.setListener(this);
        binding.listRecycler.setAdapter(new AlphaInAnimationAdapter(adapter));
        binding.listRecycler.setLayoutManager(new GridLayoutManager(activity, 3));
    }

    @Override
    public void onItemClick(ListItem item, int pos) {
        if (!(item instanceof ItemItem)) return;
        ItemItem target = (ItemItem) item;
        showCard(activity, viewModel, target, this.sortClass == 0);
    }

    @SuppressLint("SetTextI18n")
    public static void showCard(AppCompatActivity activity, final ViewModel viewModel, ItemItem target, boolean isCommon) {
        final CardFragment fragment = new CardFragment(activity);
        final ItemCardBinding itemBinding = fragment.getBinding();
        if (viewModel.isExistCollection(target.getId())) {
            itemBinding.itemCardBtnLove.setImageResource(R.drawable.ic_love_red);
        }
        // 收藏按钮
        fragment.getHandler().setOnClickCardLike(v -> {
            if (viewModel.isExistCollection(target.getId())) {
                itemBinding.itemCardBtnLove.setImageResource(R.drawable.ic_love);
                viewModel.removeCollection(target.getId());
            } else {
                itemBinding.itemCardBtnLove.setImageResource(R.drawable.ic_love_red);
                viewModel.addCollection(new CollectionItem(target.getId(),
                        isCommon ? CollectionItem.Type.Item : CollectionItem.Type.SpecialItem, "", new Date()));
            }
        });
        itemBinding.itemCardName.setText(target.getName());
        if (isCommon) {
            itemBinding.itemCardLayoutPrice.setVisibility(View.VISIBLE);
            itemBinding.itemCardLv.setVisibility(View.GONE);
            itemBinding.itemCardPrice.setText("" + target.getPrice());
            itemBinding.itemCardPriceTotal.setText("" + target.getTotalPrice());
        } else {
            itemBinding.itemCardLv.setText("等级：" + target.getLevel());
        }
        itemBinding.itemCardAttrText.setText(target.getEffect());
        if (target.getPassiveEffect() == null) {
            itemBinding.itemCardDetail.setVisibility(View.GONE);
        } else {
            itemBinding.itemCardDetail.setText(target.getPassiveEffect());
        }
        viewModel.getItemIcon(target.getId()).observe(activity, (resIcon) -> {
            if (resIcon != null && resIcon.status == Resource.Status.SUCCESS && resIcon.data != null) {
                itemBinding.itemCardIcon.setImageBitmap(resIcon.data);
            }
        });
        fragment.show(activity.getSupportFragmentManager(), "ItemDetail");

    }


    // 常规选择分类
    public void onClickSort(View v) {
        if ((v != null && this.sort == v.getId()) || this.adapter == null) return;
        if (v != null) {
            this.sort = v.getId();
            setBtnBackgroundTint(v.getId());
        }
        this.sortClass = 0;
        final String title;
        switch (this.sort) {
            case R.id.sheet_item_btn_all:
                title = "常规";
                break;
            case R.id.sheet_item_btn_attack:
                title = "攻击";
                break;
            case R.id.sheet_item_btn_magic:
                title = "法术";
                break;
            case R.id.sheet_item_btn_defense:
                title = "防御";
                break;
            case R.id.sheet_item_btn_move:
                title = "移动";
                break;
            case R.id.sheet_item_btn_jungle:
                title = "打野";
                break;
            case R.id.sheet_item_btn_auxiliary:
                title = "辅助";
                break;
            default:
                title = "常规";
        }
        binding.listCollapsingToolbar.setTitle(title + "装备");
        viewModel.getNormalItemList().observe(activity, resource -> {
            if (resource != null && resource.data != null && resource.status == Resource.Status.SUCCESS) {
                if (title.equals("常规")) {
                    this.adapter.refreshData(resource.data);
                } else {
                    List<ListItem> data = new ArrayList<>();
                    for (ItemItem item : resource.data) {
                        if (title.equals(item.getType())) {
                            data.add(item);
                        }
                    }
                    this.adapter.refreshData(data);
                }
                if (this.sheet != null) this.sheet.dismiss();
            }
        });
    }

    // 边境突围选择分类
    public void onClickSortSp(View v) {
        if ((v != null && this.sort == v.getId()) || this.adapter == null) return;
        if (v != null) {
            this.sort = v.getId();
            setBtnBackgroundTint(v.getId());
        }
        this.sortClass = 1;
        final String title;
        switch (this.sort) {
            case R.id.sheet_sp_item_btn_all:
                title = "全部";
                break;
            case R.id.sheet_sp_item_btn_equip:
                title = "装备";
                break;
            case R.id.sheet_sp_item_btn_prop:
                title = "道具";
                break;
            case R.id.sheet_sp_item_btn_skill:
                title = "额外技能";
                break;
            default:
                title = "全部";
        }
        binding.listCollapsingToolbar.setTitle(title + "(边境突围)");
        viewModel.getSpecialItemList().observe(activity, resource -> {
            if (resource != null && resource.status == Resource.Status.SUCCESS && resource.data != null) {
                if (title.equals("全部")) {
                    this.adapter.refreshData(resource.data);
                } else {
                    List<ListItem> data = new ArrayList<>();
                    for (ItemItem item : resource.data) {
                        if (title.equals(item.getType())) {
                            data.add(item);
                        }
                    }
                    this.adapter.refreshData(data);
                }
                if (this.sheet != null) this.sheet.dismiss();
            }
        });
    }


    // 切换模式
    public void onClickClass(View v) {
        setSortClassView(v.getId() == R.id.sheet_item_btn_normal ? 0 : 1);
    }

    private void setBtnBackgroundTint(int id) {
        MaterialButton buttons[] = {sheetBinding.sheetItemBtnAll, sheetBinding.sheetItemBtnAttack, sheetBinding.sheetItemBtnMagic,
                sheetBinding.sheetItemBtnDefense, sheetBinding.sheetItemBtnMove, sheetBinding.sheetItemBtnJungle, sheetBinding.sheetItemBtnAuxiliary,
                sheetBinding.sheetSpItemBtnAll, sheetBinding.sheetSpItemBtnEquip, sheetBinding.sheetSpItemBtnProp, sheetBinding.sheetSpItemBtnSkill};
        for (MaterialButton button : buttons) {
            if (button.getId() == id) {
                button.setBackgroundTintList(ContextCompat.getColorStateList(activity, R.color.colorPrimaryDark));
            } else {
                button.setBackgroundTintList(ContextCompat.getColorStateList(activity, R.color.colorBtnGray));
            }
        }
    }

    private void setSortClassView(int sortClass) {
        if (sortClass == 0) {
            sheetBinding.sheetItemBtnNormal.setBackgroundTintList(ContextCompat.getColorStateList(activity, R.color.colorPrimaryDark));
            sheetBinding.sheetItemBtnSpecial.setBackgroundTintList(ContextCompat.getColorStateList(activity, R.color.colorBtnGray));
            sheetBinding.sheetLayoutNormal.setVisibility(View.VISIBLE);
            sheetBinding.sheetLayoutSpecial.setVisibility(View.GONE);
        } else {
            sheetBinding.sheetItemBtnNormal.setBackgroundTintList(ContextCompat.getColorStateList(activity, R.color.colorBtnGray));
            sheetBinding.sheetItemBtnSpecial.setBackgroundTintList(ContextCompat.getColorStateList(activity, R.color.colorPrimaryDark));
            sheetBinding.sheetLayoutNormal.setVisibility(View.GONE);
            sheetBinding.sheetLayoutSpecial.setVisibility(View.VISIBLE);
        }

    }
}
