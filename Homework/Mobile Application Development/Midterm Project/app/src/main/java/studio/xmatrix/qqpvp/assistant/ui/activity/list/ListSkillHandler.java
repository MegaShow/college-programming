package studio.xmatrix.qqpvp.assistant.ui.activity.list;

import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.GridLayoutManager;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;

import com.scwang.smartrefresh.layout.api.RefreshLayout;

import java.util.Date;

import jp.wasabeef.recyclerview.adapters.AlphaInAnimationAdapter;
import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.data.common.Resource;
import studio.xmatrix.qqpvp.assistant.data.model.CollectionItem;
import studio.xmatrix.qqpvp.assistant.data.model.ListItem;
import studio.xmatrix.qqpvp.assistant.data.model.SummonerItem;
import studio.xmatrix.qqpvp.assistant.databinding.ItemCardBinding;
import studio.xmatrix.qqpvp.assistant.databinding.ListActivityBinding;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;
import studio.xmatrix.qqpvp.assistant.ui.fragment.card.CardFragment;

public class ListSkillHandler implements ListTypeHandler, ListAdapter.OnItemClickListener {
    private ListActivity activity;
    private ListActivityBinding binding;
    private ViewModel viewModel;

    private ListAdapter adapter;

    ListSkillHandler(ListActivity activity, ListActivityBinding binding, ViewModel viewModel) {
        this.activity = activity;
        this.binding = binding;
        this.viewModel = viewModel;
    }

    @Override
    public void initView() {
        binding.listCollapsingToolbar.setTitle("召唤师技能");
        binding.listTopImg.setImageResource(R.mipmap.list_skill_bg);
        binding.fabClass.hide();
    }

    @Override
    public void onRefresh(RefreshLayout refreshLayout) {
        viewModel.getSummonerListForcibly(activity).observe(activity, res -> {
            if (res != null && res.data != null) {
                switch (res.status) {
                    case SUCCESS:
                        binding.listNetworkError.setVisibility(View.GONE);
                        adapter.refreshData(res.data);
                        refreshLayout.finishRefresh(true);
                        break;
                    case ERROR:
                        refreshLayout.finishRefresh(false);
                        break;
                }
            }
        });
    }

    @Override
    public void initList() {
        setAdapter();
        viewModel.getSummonerList().observe(activity, resource -> {
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

    private void setAdapter() {
        adapter = new ListAdapter(activity, viewModel, 2);
        adapter.setListener(this);
        binding.listRecycler.setAdapter(new AlphaInAnimationAdapter(adapter));
        binding.listRecycler.setLayoutManager(new GridLayoutManager(activity, 3));
    }

    @Override
    public void onClickFilter() {

    }

    public static void showCard(AppCompatActivity activity, ViewModel viewModel, SummonerItem target) {
        CardFragment fragment = new CardFragment(activity);
        ItemCardBinding itemBinding = fragment.getBinding();

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
                viewModel.addCollection(new CollectionItem(target.getId(), CollectionItem.Type.Summoner, "", new Date()));
            }
        });
        itemBinding.itemCardName.setText(target.getName());
        itemBinding.itemCardLv.setText(target.getRank());
        itemBinding.itemCardAttrText.setVisibility(View.GONE);
        itemBinding.itemCardAttrPic.setVisibility(View.VISIBLE);
        itemBinding.itemCardDetail.setText(target.getDescription());
        viewModel.getSummonerIcon(target.getId()).observe(activity, (resIcon) -> {
            if (resIcon != null && resIcon.status == Resource.Status.SUCCESS && resIcon.data != null) {
                itemBinding.itemCardIcon.setImageBitmap(resIcon.data);
            }
        });
        viewModel.getSummonerPicture(target.getId()).observe(activity, (resIcon) -> {
            if (resIcon != null && resIcon.status == Resource.Status.SUCCESS && resIcon.data != null) {
                itemBinding.itemCardAttrPic.setScaleType(ImageView.ScaleType.CENTER_CROP);
                itemBinding.itemCardAttrPic.setImageBitmap(resIcon.data);
            }
        });
        fragment.show(activity.getSupportFragmentManager(), "SummonerDetail");
    }

    @Override
    public void onItemClick(ListItem item, int pos) {
        if (!(item instanceof SummonerItem)) return;
        SummonerItem target = (SummonerItem) item;
        showCard(activity, viewModel, target);
    }
}
