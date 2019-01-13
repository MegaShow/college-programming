package studio.xmatrix.qqpvp.assistant.ui.activity.herodetail;

import android.databinding.DataBindingUtil;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.ViewGroup;

import java.util.ArrayList;
import java.util.List;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.data.common.Resource;
import studio.xmatrix.qqpvp.assistant.databinding.SkinItemBinding;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;

public class SkinAdapter extends RecyclerView.Adapter<SkinAdapter.MyViewHolder> {
    private ViewModel viewModel;
    private HeroDetailActivity activity;
    private List<Integer> data;
    private Integer selected;
    private OnItemClickListener listener;

    public interface OnItemClickListener {
        void onItemClick(Integer item, int pos);
    }

    SkinAdapter(HeroDetailActivity activity, ViewModel viewModel) {
        this.viewModel = viewModel;
        this.activity = activity;
        this.data = new ArrayList<>();
        this.selected = 0;
    }

    public void setListener(SkinAdapter.OnItemClickListener listener) {
        this.listener = listener;
    }

    // 刷新数据
    void refreshData(List<Integer> data) {
        if (data == null) return;
        this.data = data;
        this.notifyDataSetChanged();
    }

    public void setSelect(Integer selected) {
        this.selected = selected;
        this.notifyDataSetChanged();
    }

    @NonNull
    @Override
    public SkinAdapter.MyViewHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int i) {
        SkinItemBinding binding = DataBindingUtil.inflate(LayoutInflater.from(activity), R.layout.skin_item, viewGroup, false);
        return new SkinAdapter.MyViewHolder(binding);
    }

    @Override
    public void onBindViewHolder(@NonNull SkinAdapter.MyViewHolder viewHolder, int i) {
        viewHolder.bind(this.data.get(i), i);
    }

    @Override
    public int getItemCount() {
        if (this.data == null) return 0;
        return this.data.size();
    }

    class MyViewHolder extends RecyclerView.ViewHolder {

        private SkinItemBinding binding;

        MyViewHolder(SkinItemBinding binding) {
            super(binding.getRoot());
            this.binding = binding;
        }

        void bind(final Integer item, int pos) {
            this.binding.skinIconLayout.setOnClickListener(v -> {
                listener.onItemClick(item, pos);
                setSelect(item);
            });
            if (item.equals(selected)) {
                this.binding.skinItemIcon.setForeground(activity.getDrawable(R.drawable.item_border_selected));
            } else {
                this.binding.skinItemIcon.setForeground(activity.getDrawable(R.drawable.item_border_none));
            }
            viewModel.getHeroSkinIcon(item).observe(activity, res -> {
                if (res == null || res.data == null || res.status != Resource.Status.SUCCESS) return;
                this.binding.skinItemIcon.setImageBitmap(res.data);
            });
        }
    }
}

