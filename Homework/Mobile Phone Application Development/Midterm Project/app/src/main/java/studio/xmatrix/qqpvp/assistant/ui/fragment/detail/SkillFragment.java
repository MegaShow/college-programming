package studio.xmatrix.qqpvp.assistant.ui.fragment.detail;

import android.annotation.SuppressLint;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import javax.annotation.Nullable;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.data.model.HeroDetailItem;
import studio.xmatrix.qqpvp.assistant.databinding.DetailSkillFragmentBinding;
import studio.xmatrix.qqpvp.assistant.ui.activity.herodetail.HeroDetailActivity;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;

@SuppressLint("ValidFragment")
public class SkillFragment extends Fragment {

    private DetailSkillFragmentBinding binding;

    @SuppressLint("ValidFragment")
    public SkillFragment(HeroDetailActivity activity, ViewModel viewModel, HeroDetailItem item) {
        this.binding = DataBindingUtil.inflate(LayoutInflater.from(activity), R.layout.detail_skill_fragment, null, false);
        binding.setHandler(new SkillHandler(binding, activity, viewModel, item));
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        return binding.getRoot();
    }
}
