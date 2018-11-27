package studio.xmatrix.qqpvp.assistant.ui.fragment.note;

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
import studio.xmatrix.qqpvp.assistant.databinding.CollectionItemNoteBinding;

@SuppressLint("ValidFragment")
public class NoteFragment extends DialogFragment {
    private CollectionItemNoteBinding binding;
    private OnEditNote onEditNote;

    @SuppressLint("ValidFragment")
    public NoteFragment(AppCompatActivity activity) {
        super();
        binding = DataBindingUtil.inflate(LayoutInflater.from(activity), R.layout.collection_item_note, null, false);
        binding.collectionNoteOk.setOnClickListener(this::onClickOK);
        binding.collectionNoteEdit.setOnEditorActionListener((v, actionId, event) -> {
            this.onClickOK(v);
            return false;
        });
    }

    public void onClickOK(View v) {
        if (onEditNote != null) onEditNote.editNote(Objects.requireNonNull(binding.collectionNoteEdit.getText()).toString());
        this.dismiss();
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        return binding.getRoot();
    }

    public void setOnEditNote(OnEditNote onEditNote) {
        this.onEditNote = onEditNote;
    }

    public interface OnEditNote {
        void editNote(String note);
    }

    public void setText(String text) {
        this.binding.collectionNoteEdit.setText(text);
        this.binding.collectionNoteEdit.setSelection(text.length());
    }


    @Override
    public void onActivityCreated(Bundle arg0) {
        super.onActivityCreated(arg0);
        Objects.requireNonNull(getDialog().getWindow()).getAttributes().windowAnimations = R.style.DialogAnimation;
    }
}
