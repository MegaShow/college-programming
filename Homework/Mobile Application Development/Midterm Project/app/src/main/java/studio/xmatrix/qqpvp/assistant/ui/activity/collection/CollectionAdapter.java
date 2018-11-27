package studio.xmatrix.qqpvp.assistant.ui.activity.collection;


import android.annotation.SuppressLint;
import android.databinding.DataBindingUtil;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.ViewGroup;

import com.daimajia.swipe.SwipeLayout;
import com.daimajia.swipe.adapters.RecyclerSwipeAdapter;

import java.util.ArrayList;
import java.util.List;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.data.common.Resource;
import studio.xmatrix.qqpvp.assistant.data.model.CollectionItem;
import studio.xmatrix.qqpvp.assistant.data.model.HeroListItem;
import studio.xmatrix.qqpvp.assistant.data.model.ItemItem;
import studio.xmatrix.qqpvp.assistant.data.model.ListItem;
import studio.xmatrix.qqpvp.assistant.data.model.SummonerItem;
import studio.xmatrix.qqpvp.assistant.databinding.CollectionItemBinding;
import studio.xmatrix.qqpvp.assistant.ui.activity.herodetail.HeroDetailActivity;
import studio.xmatrix.qqpvp.assistant.ui.activity.list.ListItemHandler;
import studio.xmatrix.qqpvp.assistant.ui.activity.list.ListSkillHandler;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;
import studio.xmatrix.qqpvp.assistant.ui.fragment.note.NoteFragment;

public class CollectionAdapter extends RecyclerSwipeAdapter<CollectionAdapter.MyViewHolder> {
    private ViewModel viewModel;
    private CollectionActivity activity;
    private List<Pair<CollectionItem, ? extends ListItem>> data;

    @Override
    public int getSwipeLayoutResourceId(int position) {
        return R.id.collection_swipe;
    }

    CollectionAdapter(CollectionActivity activity, ViewModel viewModel) {
        this.viewModel = viewModel;
        this.activity = activity;
        this.data = new ArrayList<>();
    }

    // 刷新数据
    void refreshData(List<Pair<CollectionItem, ? extends ListItem>> data) {
        if (data == null) return;
        this.notifyItemRangeRemoved(0, this.data.size());
        this.data = data;
        this.notifyItemRangeInserted(0, this.data.size());
    }

    void observeData(List<Pair<CollectionItem, ? extends ListItem>> newData) {
        if (newData == null) return;
        List<Pair<CollectionItem, ? extends ListItem>> oldData = this.data;
        this.data = newData;
        if (newData.size() > oldData.size()) {
            this.notifyItemInserted(newData.size() - 1);
        } else if (newData.size() < oldData.size()) {
            for (int i = 0; i < oldData.size(); i++) {
                if (i >= newData.size()) {
                    notifyItemRemoved(i);
                    break;
                }
                if (oldData.get(i).first.getId() != newData.get(i).first.getId()) {
                    notifyItemRemoved(i);
                    break;
                }
            }
        } else {
            this.notifyDataSetChanged();
        }
    }

    @NonNull
    @Override
    public CollectionAdapter.MyViewHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int i) {
        CollectionItemBinding binding = DataBindingUtil.inflate(LayoutInflater.from(activity), R.layout.collection_item, viewGroup, false);
        return new CollectionAdapter.MyViewHolder(binding);
    }

    @Override
    public void onBindViewHolder(@NonNull CollectionAdapter.MyViewHolder viewHolder, int i) {
        viewHolder.bind(this.data.get(i));
        mItemManger.bindView(viewHolder.itemView, i);
    }

    @Override
    public int getItemCount() {
        if (this.data == null) return 0;
        return this.data.size();
    }

    class MyViewHolder extends RecyclerView.ViewHolder {
        private CollectionItemBinding binding;

        MyViewHolder(CollectionItemBinding binding) {
            super(binding.getRoot());
            this.binding = binding;
        }

        @SuppressLint("SetTextI18n")
        void bind(final Pair<CollectionItem, ? extends ListItem> item) {
            binding.collectionSwipe.setShowMode(SwipeLayout.ShowMode.PullOut);
            binding.collectionSwipe.addDrag(SwipeLayout.DragEdge.Left, binding.collectionBottomLeft.collectionLayoutLeft);
            binding.collectionSwipe.addDrag(SwipeLayout.DragEdge.Right, binding.collectionBottomRight.collectionLayoutRight);
            switch (item.first.getType()) {
                case Hero:
                    HeroListItem hero = (HeroListItem) item.second;
                    binding.collectionSurface.cardName.setText(hero.getName());
                    binding.collectionSurface.cardTitle.setText(hero.getTypes() + " · " + hero.getDefaultSkin());
                    viewModel.getHeroIcon(hero.getId()).observe(activity, res -> {
                        if (res == null || res.data == null || res.status != Resource.Status.SUCCESS) return;
                        binding.collectionSurface.listItemIcon.setImageBitmap(res.data);
                    });
                    binding.collectionSurface.cardTypeName.setText("英雄");
                    binding.collectionSurface.cardLayoutClick.setOnClickListener(v -> HeroDetailActivity.startActivity(activity, hero.getId()));
                    break;
                case Item:
                    ItemItem itemItem = (ItemItem) item.second;
                    binding.collectionSurface.cardName.setText(itemItem.getName());
                    binding.collectionSurface.cardTitle.setText("常规装备");
                    viewModel.getItemIcon(itemItem.getId()).observe(activity, res -> {
                        if (res == null || res.data == null || res.status != Resource.Status.SUCCESS) return;
                        binding.collectionSurface.listItemIcon.setImageBitmap(res.data);
                    });
                    binding.collectionSurface.cardTypeName.setText("装备");
                    binding.collectionSurface.cardLayoutClick.setOnClickListener(v -> ListItemHandler.showCard(activity, viewModel, itemItem, false));
                    break;
                case SpecialItem:
                    ItemItem specialItem = (ItemItem) item.second;
                    binding.collectionSurface.cardName.setText(specialItem.getName());
                    binding.collectionSurface.cardTitle.setText("常规装备");
                    viewModel.getItemIcon(specialItem.getId()).observe(activity, res -> {
                        if (res == null || res.data == null || res.status != Resource.Status.SUCCESS) return;
                        binding.collectionSurface.listItemIcon.setImageBitmap(res.data);
                    });
                    binding.collectionSurface.cardTypeName.setText("装备");
                    binding.collectionSurface.cardLayoutClick.setOnClickListener(v -> ListItemHandler.showCard(activity, viewModel, specialItem, true));
                    break;

                case Summoner:
                    SummonerItem summoner = (SummonerItem) item.second;
                    binding.collectionSurface.cardName.setText(summoner.getName());
                    binding.collectionSurface.cardTitle.setText(summoner.getRank());
                    viewModel.getSummonerIcon(summoner.getId()).observe(activity, res -> {
                        if (res == null || res.data == null || res.status != Resource.Status.SUCCESS) return;
                        binding.collectionSurface.listItemIcon.setImageBitmap(res.data);
                    });
                    binding.collectionSurface.cardTypeName.setText("技能");
                    binding.collectionSurface.cardLayoutClick.setOnClickListener(v -> ListSkillHandler.showCard(activity, viewModel, summoner));
                    break;
            }
            if (!item.first.getRemark().equals("")) {
                binding.collectionSurface.cardName.setText(binding.collectionSurface.cardName.getText() + "("+item.first.getRemark()+")");
                binding.collectionBottomLeft.collectionNoteText.setText("修改备注");
            } else {
                binding.collectionBottomLeft.collectionNoteText.setText("添加备注");
            }
            binding.collectionBottomLeft.collectionLayoutLeft.setOnClickListener(v -> {
                for (int i = 0; i < data.size(); i++) {
                    if (data.get(i).first.getId() == item.first.getId()) {
                        NoteFragment noteFragment = new NoteFragment(activity);
                        if (!item.first.getRemark().equals("")) noteFragment.setText(item.first.getRemark());
                        noteFragment.setOnEditNote(s -> {
                            item.first.setRemark(s);
                            viewModel.updateCollection(item.first);
                            mItemManger.closeAllItems();
                        });
                        noteFragment.show(activity.getSupportFragmentManager(), "note");
                        break;
                    }
                }
            });
            binding.collectionBottomRight.collectionLayoutRight.setOnClickListener(v -> {
                for (int i = 0; i < data.size(); i++) {
                    if (data.get(i).first.getId() == item.first.getId()) {
                        viewModel.removeCollection(item.first.getId());
                        mItemManger.closeAllItems();
                        break;
                    }
                }
            });
        }
    }
}
