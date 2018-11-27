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
import studio.xmatrix.qqpvp.assistant.databinding.ItemSheetFragmentBinding;

@SuppressLint("ValidFragment")
public class ItemSheetFragment extends BottomSheetDialogFragment {
    ItemSheetFragmentBinding binding;
    ItemSheetFragment.AfterBinding inter;

    public interface AfterBinding {
        void getBinding(ItemSheetFragmentBinding binding);
    }

    @SuppressLint("ValidFragment")
    public ItemSheetFragment(ItemSheetFragment.AfterBinding inter) {
        this.inter = inter;
    }

    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        BottomSheetDialog dialog = (BottomSheetDialog) super.onCreateDialog(savedInstanceState);

        View view = View.inflate(getContext(), R.layout.item_sheet_fragment, null);
        dialog.setContentView(view);
        binding = DataBindingUtil.bind(view);
        inter.getBinding(binding);

        View parent = ((View) view.getParent());
        parent.setBackgroundColor(Color.TRANSPARENT);
        // parent.setPadding(40, 0, 40, 0);
        return dialog;
    }
}