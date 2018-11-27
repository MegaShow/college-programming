package studio.xmatrix.qqpvp.assistant.ui.fragment.detail;

import android.os.Handler;
import android.view.animation.AlphaAnimation;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

import studio.xmatrix.qqpvp.assistant.data.common.Resource;
import studio.xmatrix.qqpvp.assistant.data.model.HeroDetailItem;
import studio.xmatrix.qqpvp.assistant.data.model.InscriptionItem;
import studio.xmatrix.qqpvp.assistant.data.model.ItemItem;
import studio.xmatrix.qqpvp.assistant.databinding.DetailEquipmentFragmentBinding;
import studio.xmatrix.qqpvp.assistant.ui.activity.herodetail.HeroDetailActivity;
import studio.xmatrix.qqpvp.assistant.ui.activity.list.ListItemHandler;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;

public class EquipmentHandler {
    private DetailEquipmentFragmentBinding binding;
    private HeroDetailItem item;
    private HeroDetailActivity activity;
    private ViewModel viewModel;
    private String[] firstItems;
    private String[] secondItems;
    private String[] suggestInscription;

    private String firstDescription;
    private String secondDescription;

    private int itemsType = 0; // 0-推荐出装1 1-推荐出装2


    EquipmentHandler(DetailEquipmentFragmentBinding binding, HeroDetailActivity activity, ViewModel viewModel, HeroDetailItem item) {
        this.binding = binding;
        this.activity = activity;
        this.viewModel = viewModel;
        this.item = item;
        initView();
    }


    private void initView() {
        firstItems = item.getSuggestFirstItems().split("\\|");
        secondItems = item.getSuggestSecondItems().split("\\|");
        suggestInscription = item.getSuggestInscriptions().split("\\|");


        firstDescription = item.getSuggestFirstItemsDescription();
        secondDescription = item.getSuggestSecondItemsDescription();

        setItem(firstItems, firstDescription);

        this.binding.equipmentRefresh.setOnClickListener(v -> {
            switch (itemsType) {
                case 0:
                    itemsType = 1;
                    setItem(secondItems, secondDescription);
                    break;
                case 1:
                    itemsType = 0;
                    setItem(firstItems, firstDescription);
                    break;
            }
        });

        this.viewModel.getInscriptionIcon(Integer.parseInt(suggestInscription[0])).observe(activity, resource -> {
            if (resource == null || resource.data == null || resource.status != Resource.Status.SUCCESS)
                return;
            this.binding.inscriptionRecommendImg1.setImageBitmap(resource.data);
        });

        this.viewModel.getInscriptionIcon(Integer.parseInt(suggestInscription[1])).observe(activity, resource -> {
            if (resource == null || resource.data == null || resource.status != Resource.Status.SUCCESS)
                return;
            this.binding.inscriptionRecommendImg2.setImageBitmap(resource.data);
        });

        this.viewModel.getInscriptionIcon(Integer.parseInt(suggestInscription[2])).observe(activity, resource -> {
            if (resource == null || resource.data == null || resource.status != Resource.Status.SUCCESS)
                return;
            this.binding.inscriptionRecommendImg3.setImageBitmap(resource.data);
        });

        this.viewModel.getInscriptionList().observe(activity, resource -> {
            if (resource == null || resource.data == null || resource.status != Resource.Status.SUCCESS)
                return;
            List<String> name = new ArrayList<>();
            List<String> description = new ArrayList<>();
            for (String inscriptionId : suggestInscription) {
                for (InscriptionItem i : resource.data) {
                    if (inscriptionId.equals(Integer.toString(i.getId()))) {
                        name.add(i.getName());
                        description.add(i.getDescription());
                    }
                }
            }
            this.binding.inscriptionRecommendName1.setText(name.get(0));
            this.binding.inscriptionRecommendAttr1.setText(description.get(0));
            this.binding.inscriptionRecommendName2.setText(name.get(1));
            this.binding.inscriptionRecommendAttr2.setText(description.get(1));
            this.binding.inscriptionRecommendName3.setText(name.get(2));
            this.binding.inscriptionRecommendAttr3.setText(description.get(2));
        });

        this.binding.inscriptionTip.setText(item.getSuggestInscriptionsDescription());
    }

    private void setItem(String[] ItemList, String description) {
        final LinearLayout linearLayouts[] = {binding.equipLayout1, binding.equipLayout2, binding.equipLayout3,
                binding.equipLayout4, binding.equipLayout5, binding.equipLayout6};
        final ImageView equipmentImages[] =  {binding.equipment1, binding.equipment2, binding.equipment3,
                binding.equipment4, binding.equipment5, binding.equipment6};
        final TextView equipmentTexts[] = {binding.equipmentText1, binding.equipmentText2, binding.equipmentText3,
        binding.equipmentText4, binding.equipmentText5, binding.equipmentText6};

        binding.equipmentTip.setText(description);
        viewModel.getNormalItemList().observe(activity, resource -> {
            if (resource == null || resource.data == null || resource.status != Resource.Status.SUCCESS)
                return;
            final List<ItemItem> items = new ArrayList<>();
            for (String item : ItemList) {
                for (ItemItem i : resource.data) {
                    if (item.equals(Integer.toString(i.getId()))) {
                        items.add(i);
                    }
                }
            }
            for (int i = 0; i < linearLayouts.length; i++) {
                // 动画效果
                final int finalI = i;
                AlphaAnimation alphaAnimation = new AlphaAnimation(1, 0);
                alphaAnimation.setDuration(200 + i * 30);
                alphaAnimation.setFillBefore(true);
                linearLayouts[i].startAnimation(alphaAnimation);
                // 点击事件
                linearLayouts[i].setOnClickListener(v -> ListItemHandler.showCard(activity,viewModel, items.get(finalI), true));
                // 设置图标和数据
                this.viewModel.getItemIcon(Integer.parseInt(ItemList[i])).observe(activity, res -> {
                    if (res == null || res.data == null || res.status != Resource.Status.SUCCESS)
                        return;
                    (new Handler()).postDelayed(() -> {
                        equipmentImages[finalI].setImageBitmap(res.data);
                        equipmentTexts[finalI].setText(items.get(finalI).getName());
                    }, 200);
                });
            }
        });

    }
}
