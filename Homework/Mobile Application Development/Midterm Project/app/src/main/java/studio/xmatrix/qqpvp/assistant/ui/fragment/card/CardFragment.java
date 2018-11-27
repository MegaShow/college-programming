package studio.xmatrix.qqpvp.assistant.ui.fragment.card;

import android.annotation.SuppressLint;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.DialogFragment;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import java.util.Objects;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.databinding.ItemCardBinding;

@SuppressLint("ValidFragment")
public class CardFragment extends DialogFragment {
    private ItemCardBinding binding;
    private CardHandler handler;

    @SuppressLint("ValidFragment")
    public CardFragment(AppCompatActivity activity) {
        super();
        binding = DataBindingUtil.inflate(LayoutInflater.from(activity), R.layout.item_card, null, false);
        handler = new CardHandler(this, binding, activity);
        binding.setHandler(handler);
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        return binding.getRoot();
    }

    public ItemCardBinding getBinding() {
        return binding;
    }

    public CardHandler getHandler() {
        return handler;
    }

    @Override
    public void onActivityCreated(Bundle arg0) {
        super.onActivityCreated(arg0);
        Objects.requireNonNull(getDialog().getWindow()).getAttributes().windowAnimations = R.style.DialogAnimation;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

    }
}
