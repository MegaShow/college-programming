package studio.xmatrix.qqpvp.assistant.ui.fragment.detail;

import android.annotation.SuppressLint;
import android.view.View;
import android.widget.ImageView;

import java.util.ArrayList;
import java.util.List;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.data.common.Resource;
import studio.xmatrix.qqpvp.assistant.data.model.HeroDetailItem;
import studio.xmatrix.qqpvp.assistant.data.model.SummonerItem;
import studio.xmatrix.qqpvp.assistant.databinding.DetailSkillFragmentBinding;
import studio.xmatrix.qqpvp.assistant.ui.activity.herodetail.HeroDetailActivity;
import studio.xmatrix.qqpvp.assistant.ui.activity.list.ListSkillHandler;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;

public class SkillHandler {
    private DetailSkillFragmentBinding binding;
    private HeroDetailItem item;
    private HeroDetailActivity activity;
    private ViewModel viewModel;
    private List<HeroDetailItem.Skill> skills;

    SkillHandler(DetailSkillFragmentBinding binding, HeroDetailActivity activity, ViewModel viewModel, HeroDetailItem item) {
        this.binding = binding;
        this.activity = activity;
        this.viewModel = viewModel;
        this.item = item;
        initView();
    }

    @SuppressLint("SetTextI18n")
    private void initView() {
        skills = item.getSkills();
        changeSkill(0);

        ImageView skillImages[] = {binding.skill1, binding.skill2, binding.skill3, binding.skill4, binding.skill5};

        for (int i = 0; i < skillImages.length; i++) {
            int finalI = i;
            skillImages[i].setOnClickListener(v-> changeSkill(finalI));
            if (i < 4) {
                this.viewModel.getHeroSkillIcon(i).observe(activity, resource->{
                    if (resource == null || resource.data == null || resource.status != Resource.Status.SUCCESS) return;
                    skillImages[finalI].setImageBitmap(resource.data);
                });
            } else {
                if(skills.size() == 5){
                    this.viewModel.getHeroSkillIcon(4).observe(activity, resource->{
                        if (resource == null || resource.data == null || resource.status != Resource.Status.SUCCESS) return;
                        this.binding.skill5.setImageBitmap(resource.data);
                        this.binding.skill5.setVisibility(View.VISIBLE);
                    });
                } else {
                    this.binding.skill5.setVisibility(View.GONE);
                }
            }
        }

        this.viewModel.getHeroSkillIcon(item.getSuggestFirstSkill()).observe(activity, resource->{
            if (resource == null || resource.data == null || resource.status != Resource.Status.SUCCESS) return;
            this.binding.mainRecommendImg.setImageBitmap(resource.data);
            this.binding.mainRecommendName.setText(skills.get(item.getSuggestFirstSkill()).getName());
        });

        this.viewModel.getHeroSkillIcon(item.getSuggestSecondSkill()).observe(activity, resource->{
            if (resource == null || resource.data == null || resource.status != Resource.Status.SUCCESS) return;
            this.binding.viceRecommendImg.setImageBitmap(resource.data);
            this.binding.viceRecommendName.setText(skills.get(item.getSuggestSecondSkill()).getName());
        });

        String[] summoners = item.getSuggestSummoners().split("\\|");

        this.viewModel.getSummonerIcon(Integer.parseInt(summoners[0])).observe(activity, resource ->{
            if (resource == null || resource.data == null || resource.status != Resource.Status.SUCCESS) return;
            this.binding.playerSkill1.setImageBitmap(resource.data);
        });

        this.viewModel.getSummonerIcon(Integer.parseInt(summoners[1])).observe(activity, resource ->{
            if (resource == null || resource.data == null || resource.status != Resource.Status.SUCCESS) return;
            this.binding.playerSkill2.setImageBitmap(resource.data);
        });

        this.viewModel.getSummonerList().observe(activity, resource->{
            if (resource == null || resource.data == null || resource.status != Resource.Status.SUCCESS) return;
            List<SummonerItem> skills = new ArrayList<>();
            for(String id : summoners){
                for(SummonerItem summoner : resource.data){
                    if(id.equals(Integer.toString(summoner.getId()))){
                        skills.add(summoner);
                        break;
                    }
                }
            }
            this.binding.playerSkill.setText(skills.get(0).getName() + "/" + skills.get(1).getName());
            this.binding.playerSkill1.setOnClickListener(v -> ListSkillHandler.showCard(activity, viewModel, skills.get(0)));
            this.binding.playerSkill2.setOnClickListener(v -> ListSkillHandler.showCard(activity, viewModel, skills.get(1)));
        });

    }

    private void changeSkill(int index){
        this.binding.skill1.setBackgroundResource(R.drawable.skill_border);
        this.binding.skill2.setBackgroundResource(R.drawable.skill_border);
        this.binding.skill3.setBackgroundResource(R.drawable.skill_border);
        this.binding.skill4.setBackgroundResource(R.drawable.skill_border);
        this.binding.skill5.setBackgroundResource(R.drawable.skill_border);
        switch (index) {
            case 0:
                this.binding.skill1.setBackgroundResource(R.drawable.skill_select_border);
                break;
            case 1:
                this.binding.skill2.setBackgroundResource(R.drawable.skill_select_border);
                break;
            case 2:
                this.binding.skill3.setBackgroundResource(R.drawable.skill_select_border);
                break;
            case 3:
                this.binding.skill4.setBackgroundResource(R.drawable.skill_select_border);
                break;
            case 4:
                this.binding.skill5.setBackgroundResource(R.drawable.skill_select_border);
                break;
        }

        this.binding.skillName.setText(skills.get(index).getName());
        this.binding.skillCd.setText(skills.get(index).getCd());
        this.binding.skillConsume.setText(skills.get(index).getConsume());
        this.binding.skillDescription.setText(skills.get(index).getDescription());
        this.binding.skillTip.setText(skills.get(index).getTips());
    }
}
