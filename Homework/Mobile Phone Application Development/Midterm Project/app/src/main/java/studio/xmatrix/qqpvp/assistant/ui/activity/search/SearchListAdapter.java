package studio.xmatrix.qqpvp.assistant.ui.activity.search;

import android.databinding.DataBindingUtil;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.ViewGroup;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.data.common.Resource;
import studio.xmatrix.qqpvp.assistant.data.model.SearchItem;
import studio.xmatrix.qqpvp.assistant.databinding.ListItemCardBinding;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;

public class SearchListAdapter extends RecyclerView.Adapter<SearchListAdapter.MyViewHolder> {
    private ViewModel viewModel;
    private SearchActivity activity;
    private List<SearchItem> data;
    private OnItemClickListener listener;
    public interface OnItemClickListener {
        void onItemClick(SearchItem item, int pos);
    }

    SearchListAdapter(SearchActivity activity, ViewModel viewModel) {
        this.viewModel = viewModel;
        this.activity = activity;
        this.data = new ArrayList<>();
    }

    // 刷新数据
    void refreshData(List<SearchItem> data) {
        if (data == null) return;
        this.notifyItemRangeRemoved(0, this.data.size());
        this.data = data;
        this.notifyItemRangeInserted(0, this.data.size());
    }

    void addData(List<SearchItem> item) {
        this.data.addAll(item);
    }

    @NonNull
    @Override
    public SearchListAdapter.MyViewHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int i) {
        ListItemCardBinding binding = DataBindingUtil.inflate(LayoutInflater.from(activity), R.layout.list_item_card, viewGroup, false);
        return new SearchListAdapter.MyViewHolder(binding);
    }

    @Override
    public void onBindViewHolder(@NonNull SearchListAdapter.MyViewHolder viewHolder, int i) {
        viewHolder.bind(this.data.get(i), i);
    }

    @Override
    public int getItemCount() {
        if (this.data == null) return 0;
        return this.data.size();
    }

    public void setListener(OnItemClickListener listener) {
        this.listener = listener;
    }

    class MyViewHolder extends RecyclerView.ViewHolder {

        private ListItemCardBinding binding;

        MyViewHolder(ListItemCardBinding binding) {
            super(binding.getRoot());
            this.binding = binding;
        }

        void bind(final SearchItem item, int pos) {
            binding.cardLayoutClick.setOnClickListener(v -> listener.onItemClick(item, pos));
            binding.cardName.setText(item.getName());
            binding.cardTitle.setText(item.getTitle());
            switch (item.getType()) {
                case HERO:
                    binding.cardTypeName.setText("英雄");
                    viewModel.getHeroIcon(item.getId()).observe(activity, resource -> {
                        if (Objects.requireNonNull(resource).status == Resource.Status.SUCCESS && resource.data != null) {
                            binding.listItemIcon.setImageBitmap(resource.data);
                        }
                    });
                    break;
                case SKILL:
                    binding.cardTypeName.setText("技能");
                    viewModel.getSummonerIcon(item.getId()).observe(activity, resource -> {
                        if (Objects.requireNonNull(resource).status == Resource.Status.SUCCESS && resource.data != null) {
                            binding.listItemIcon.setImageBitmap(resource.data);
                        }
                    });
                    break;
                case ITEM:
                case SPITEM:
                    binding.cardTypeName.setText("装备");
                    viewModel.getItemIcon(item.getId()).observe(activity, resource -> {
                        if (Objects.requireNonNull(resource).status == Resource.Status.SUCCESS && resource.data != null) {
                            binding.listItemIcon.setImageBitmap(resource.data);
                        }
                    });
                    break;
            }
        }
    }
}
