package com.icytown.course.experimenttwo.presentation.foodlist;

import android.content.Context;
import android.content.DialogInterface;
import android.support.v7.app.AlertDialog;
import android.support.v7.widget.LinearLayoutManager;
import android.util.Pair;
import android.view.View;
import android.widget.Toast;

import com.icytown.course.experimenttwo.R;
import com.icytown.course.experimenttwo.data.model.FoodItem;
import com.icytown.course.experimenttwo.data.viewmodel.FoodListViewModel;
import com.icytown.course.experimenttwo.databinding.ActivityFoodListBinding;
import com.icytown.course.experimenttwo.presentation.fooddetail.FoodDetailActivity;
import com.icytown.course.experimenttwo.receiver.StaticReceiver;
import com.icytown.course.experimenttwo.receiver.WidgetProvider;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.Random;

public class FoodListHandler {

    private Context mContext;
    private ActivityFoodListBinding mBinding;
    private FoodListViewModel mViewModel;

    private boolean isShowCollection = false;

    public FoodListHandler(Context context, ActivityFoodListBinding binding, FoodListViewModel viewModel) {
        mContext = context;
        mBinding = binding;
        mViewModel = viewModel;

        initRecyclerView();
        initListView();

        Random random = new Random();
        int i = random.nextInt(viewModel.getData().size());
        StaticReceiver.sendStaticAction(mContext, viewModel.getData().get(i), i);
        WidgetProvider.sendStaticAction(mContext, viewModel.getData().get(i), i);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onEvent(Pair<FoodItem, Integer> event) {
        updateFoodList(event.first, event.second);
    }

    public void onClickFAB(View view) {
        if (isShowCollection) {
            showCollection(false);
        } else {
            showCollection(true);
        }
    }

    public void showCollection(boolean show) {
        if (show) {
            mBinding.foodList.setVisibility(View.GONE);
            mBinding.foodCollectionList.setVisibility(View.VISIBLE);
            mBinding.floatingActionButton.setImageResource(R.mipmap.mainpage);
            isShowCollection = true;
        } else {
            mBinding.foodList.setVisibility(View.VISIBLE);
            mBinding.foodCollectionList.setVisibility(View.GONE);
            mBinding.floatingActionButton.setImageResource(R.mipmap.collect);
            isShowCollection = false;
        }
    }

    public void turnToFoodDetailActivity(FoodItem item, int requestCode) {
        final int index = mViewModel.getData().indexOf(item);
        if (index == -1) {
            return;
        } else if (index == 0 && requestCode == FoodListActivity.REQUESTCODE_LISTVIEW) {
            return;
        }
        FoodDetailActivity.startActivity(mContext, item, index);
    }

    public void updateFoodList(FoodItem item, int index) {
        mViewModel.updateItem(item, index);
    }

    public boolean removeFromRecyclerView(FoodItem item) {
        if (mViewModel.removeItem(item)) {
            Toast.makeText(mContext, "删除" + item.getName(), Toast.LENGTH_SHORT).show();
            return true;
        }
        return false;
    }

    public boolean removeFromListView(final FoodItem item) {
        if (mViewModel.getCollectData().indexOf(item) == 0) {
            return true;
        }
        AlertDialog.Builder builder = new AlertDialog.Builder(mContext);
        builder.setTitle("删除")
                .setMessage("确定删除" + item.getName() + "?")
                .setNegativeButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                    }
                })
                .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        mViewModel.removeCollectItem(item);
                    }
                });
        builder.create().show();
        return true;
    }

    private void initRecyclerView() {
        LinearLayoutManager layoutManager = new LinearLayoutManager(mContext);
        FoodAdapter adapter = new FoodAdapter(mViewModel.getData());
        mBinding.foodList.setLayoutManager(layoutManager);
        mBinding.foodList.setAdapter(adapter);
        mViewModel.setAdapter(adapter);
    }

    private void initListView() {
        FoodCollectionAdapter adapter = new FoodCollectionAdapter(mContext, R.layout.item_food, mViewModel.getCollectData());
        mBinding.foodCollectionList.setAdapter(adapter);
        mViewModel.setCollectAdapter(adapter);
    }
}
