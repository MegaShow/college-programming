package studio.xmatrix.qqpvp.assistant.ui.fragment.detail;

import java.util.ArrayList;
import java.util.List;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.data.model.HeroDetailItem;
import studio.xmatrix.qqpvp.assistant.databinding.DetailIntroductionFragmentBinding;
import studio.xmatrix.qqpvp.assistant.ui.activity.herodetail.HeroDetailActivity;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;

public class IntroductionHandler {

    private DetailIntroductionFragmentBinding binding;
    private HeroDetailItem item;
    private HeroDetailActivity activity;
    private ViewModel viewModel;
    private List<HeroDetailItem.Relation> relationNow;

    IntroductionHandler(DetailIntroductionFragmentBinding binding, HeroDetailActivity activity, ViewModel viewModel, HeroDetailItem item) {
        this.binding = binding;
        this.activity = activity;
        this.viewModel = viewModel;
        this.item = item;
        initView();
    }

    private void initView() {

        this.binding.progressSurvive.setProgress(item.getAttrViability());
        this.binding.numberSurvive.setText(String.valueOf(item.getAttrViability()/10));
        this.binding.progressAttack.setProgress(item.getAttrAttack());
        this.binding.numberAttack.setText(String.valueOf(item.getAttrAttack()/10));
        this.binding.progressSkill.setProgress(item.getAttrSkill());
        this.binding.numberSkill.setText(String.valueOf(item.getAttrSkill()/10));
        this.binding.progressDifficulty.setProgress(item.getAttrDifficulty());
        this.binding.numberDifficulty.setText(String.valueOf(item.getAttrDifficulty()/10));

        this.binding.heroRelationPartner.setOnClickListener(v-> relationchange(0));

        this.binding.heroRelationSuppress.setOnClickListener(v-> relationchange(1));

        this.binding.heroRelationSuppressed.setOnClickListener(v-> relationchange(2));

        this.binding.heroRelationHero1.setOnClickListener(v-> descriptionChange(0));

        this.binding.heroRelationHero2.setOnClickListener(v-> descriptionChange(1));

        this.binding.heroRelationHero1.setOnLongClickListener(v -> {
            HeroDetailActivity.startActivity(activity, relationNow.get(0).getId());
            return true;
        });

        this.binding.heroRelationHero2.setOnLongClickListener(v -> {
            HeroDetailActivity.startActivity(activity, relationNow.get(1).getId());
            return true;
        });

        this.binding.heroStory.setText(item.getStory());

        setRelationHero(0);

        descriptionChange(0);
    }

    private void descriptionChange(int i) {
        this.binding.heroRelationHero1.setForeground(activity.getDrawable(R.drawable.item_border));
        this.binding.heroRelationHero2.setForeground(activity.getDrawable(R.drawable.item_border));
        switch (i) {
            case 0:
                this.binding.heroRelationDescription.setText(relationNow.get(0).getDescription());
                this.binding.heroRelationHero1.setForeground(activity.getDrawable(R.drawable.item_select_border));
                break;
            case 1:
                this.binding.heroRelationDescription.setText(relationNow.get(1).getDescription());
                this.binding.heroRelationHero2.setForeground(activity.getDrawable(R.drawable.item_select_border));
                break;
        }
    }

    private void relationchange(int relationType) {
        this.binding.heroRelationPartner.setImageResource(R.drawable.ic_relation_partner);
        this.binding.heroRelationSuppress.setImageResource(R.drawable.ic_relation_supress);
        this.binding.heroRelationSuppressed.setImageResource(R.drawable.ic_relation_supressed);
        descriptionChange(0);
        String RelationType = "";
        switch (relationType) {
            case 0:
                this.binding.heroRelationPartner.setImageResource(R.drawable.ic_relation_partner_selected);
                RelationType = "最佳伙伴";
                setRelationHero(0);
                break;
            case 1:
                this.binding.heroRelationSuppress.setImageResource(R.drawable.ic_relation_supress_selected);
                RelationType = "克制英雄";
                setRelationHero(1);
                break;
            case 2:
                this.binding.heroRelationSuppressed.setImageResource(R.drawable.ic_relation_supressed_selected);
                RelationType = "被克制英雄";
                setRelationHero(2);
                break;
        }
        this.binding.heroRelationType.setText(RelationType);
    }

    private void setRelationHero(int type) {
        List<HeroDetailItem.Relation> relations = this.item.getRelations();
        relationNow = new ArrayList<>();
        for(HeroDetailItem.Relation relation : relations){
            switch (type){
                case 0:
                    if (relation.isBestPartner()) relationNow.add(relation);
                    break;
                case 1:
                    if (relation.isLoser()) relationNow.add(relation);
                    break;
                case 2:
                    if (relation.isWinner()) relationNow.add(relation);
                    break;
            }
        }

        this.binding.heroRelationDescription.setText(relationNow.get(0).getDescription());

        this.viewModel.getHeroIcon(relationNow.get(0).getId()).observe(activity, resource ->{
            if (resource == null || resource.data == null) return;
            switch (resource.status) {
                case SUCCESS:
                    this.binding.heroRelationHero1.setImageBitmap(resource.data);
                    break;
            }
        });

        this.viewModel.getHeroIcon(relationNow.get(1).getId()).observe(activity, resource ->{
            if (resource == null || resource.data == null) return;
            switch (resource.status) {
                case SUCCESS:
                    this.binding.heroRelationHero2.setImageBitmap(resource.data);
                    break;
            }
        });
    }
}
