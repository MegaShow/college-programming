package studio.xmatrix.qqpvp.assistant.ui.activity.list;

import android.databinding.DataBindingUtil;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.data.common.Resource;
import studio.xmatrix.qqpvp.assistant.data.model.HeroListItem;
import studio.xmatrix.qqpvp.assistant.data.model.ListItem;
import studio.xmatrix.qqpvp.assistant.databinding.ListItemBinding;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;

public class ListAdapter extends RecyclerView.Adapter<ListAdapter.MyViewHolder> {
    private ViewModel viewModel;
    private ListActivity activity;
    private List<ListItem> data;
    private int type;
    private OnItemClickListener listener;

    public interface OnItemClickListener {
        void onItemClick(ListItem item, int pos);
    }

    ListAdapter(ListActivity activity, ViewModel viewModel, int type) {
        this.viewModel = viewModel;
        this.activity = activity;
        this.data = new ArrayList<>();
        this.type = type;
    }

    public void setListener(OnItemClickListener listener) {
        this.listener = listener;
    }

    // 刷新数据
    void refreshData(List<? extends ListItem> data) {
        if (data == null) return;
        this.notifyItemRangeRemoved(0, this.data.size());
        this.data.clear();
        this.data.addAll(data);
        this.notifyItemRangeInserted(0, this.data.size());
    }

    void addData(List<? extends ListItem> item) {
        int oldSize = this.data.size();
        this.data.addAll(item);
        notifyItemRangeInserted(oldSize, this.data.size());
    }

    @NonNull
    @Override
    public MyViewHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int i) {
        ListItemBinding binding = DataBindingUtil.inflate(LayoutInflater.from(activity), R.layout.list_item, viewGroup, false);
        return new MyViewHolder(binding);
    }

    @Override
    public void onBindViewHolder(@NonNull MyViewHolder viewHolder, int i) {
        viewHolder.bind(this.data.get(i), i);
    }

    @Override
    public int getItemCount() {
        if (this.data == null) return 0;
        return this.data.size();
    }

    class MyViewHolder extends RecyclerView.ViewHolder {

        private ListItemBinding binding;

        MyViewHolder(ListItemBinding binding) {
            super(binding.getRoot());
            this.binding = binding;
        }

        void bind(final ListItem item, int pos) {
            this.itemView.setOnClickListener(v -> listener.onItemClick(item, pos));
            binding.itemHeroName.setText(item.getName());
            binding.itemBadgeFree.setVisibility(View.GONE);
            binding.itemBadgeNew.setVisibility(View.GONE);
            if (type == 0) {
                viewModel.getHeroIcon(item.getId()).observe(activity, resource -> {
                    if (Objects.requireNonNull(resource).status == Resource.Status.SUCCESS && resource.data != null) {
                        binding.itemAvatar.setImageBitmap(resource.data);
                    }
                });
                binding.itemAvatar.setForeground(activity.getDrawable(R.drawable.item_border));
                if (item instanceof HeroListItem) {
                    HeroListItem heroItem = (HeroListItem) item;
                    if (heroItem.isFreeHero()) {
                        binding.itemBadgeFree.setVisibility(View.VISIBLE);
                    } else if (heroItem.isNewHero()) {
                        binding.itemBadgeNew.setVisibility(View.VISIBLE);
                    }
                }
            } else if (type == 1) {
                viewModel.getItemIcon(item.getId()).observe(activity, resource -> {
                    if (Objects.requireNonNull(resource).status == Resource.Status.SUCCESS && resource.data != null) {
                        binding.itemAvatar.setImageBitmap(resource.data);
                    }
                });
                binding.itemAvatar.setForeground(activity.getDrawable(R.drawable.item_border_other));
            } else if (type == 2) {
                viewModel.getSummonerIcon(item.getId()).observe(activity, resource -> {
                    if (Objects.requireNonNull(resource).status == Resource.Status.SUCCESS && resource.data != null) {
                        binding.itemAvatar.setImageBitmap(resource.data);
                    }
                });
                binding.itemAvatar.setForeground(activity.getDrawable(R.drawable.item_border_other));
            }
        }
    }
}
