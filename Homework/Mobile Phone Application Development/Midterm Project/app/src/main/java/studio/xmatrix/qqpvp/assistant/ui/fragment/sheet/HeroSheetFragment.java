package studio.xmatrix.qqpvp.assistant.ui.fragment.sheet;

import android.annotation.SuppressLint;
import android.app.Dialog;
import android.databinding.DataBindingUtil;
import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.design.widget.BottomSheetDialog;
import android.support.design.widget.BottomSheetDialogFragment;
import android.view.View;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.databinding.HeroSheetFragmentBinding;

@SuppressLint("ValidFragment")
public class HeroSheetFragment extends BottomSheetDialogFragment {
    HeroSheetFragmentBinding binding;
    AfterBinding inter;

    public interface AfterBinding {
        void getBinding(HeroSheetFragmentBinding binding);
    }

    @SuppressLint("ValidFragment")
    public HeroSheetFragment(AfterBinding inter) {
        this.inter = inter;
    }

    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        BottomSheetDialog dialog = (BottomSheetDialog) super.onCreateDialog(savedInstanceState);

        View view = View.inflate(getContext(), R.layout.hero_sheet_fragment, null);
        dialog.setContentView(view);
        binding = DataBindingUtil.bind(view);
        inter.getBinding(binding);

        View parent = ((View) view.getParent());
        parent.setBackgroundColor(Color.TRANSPARENT);
        // parent.setPadding(40, 0, 40, 0);
        return dialog;
    }
}
