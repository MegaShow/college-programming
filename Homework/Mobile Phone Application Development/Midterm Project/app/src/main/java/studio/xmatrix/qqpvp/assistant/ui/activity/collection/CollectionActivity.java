package studio.xmatrix.qqpvp.assistant.ui.activity.collection;

import android.app.Activity;
import android.content.Intent;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.databinding.CollectionActivityBinding;

public class CollectionActivity extends AppCompatActivity {

    CollectionActivityBinding binding;
    CollectionHandler handler;

    public static void startActivity(Activity activity) {
        activity.startActivity(new Intent(activity, CollectionActivity.class));
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.binding = DataBindingUtil.setContentView(this, R.layout.collection_activity);
        this.handler = new CollectionHandler(this, this.binding);
    }

}
