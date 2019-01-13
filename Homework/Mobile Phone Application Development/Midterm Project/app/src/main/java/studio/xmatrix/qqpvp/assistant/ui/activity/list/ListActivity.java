package studio.xmatrix.qqpvp.assistant.ui.activity.list;

import android.app.Activity;
import android.content.Intent;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.IdRes;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.databinding.ListActivityBinding;

public class ListActivity extends AppCompatActivity {

    private ListHandler handler;
    ListActivityBinding binding;

    public static void startActivity(Activity activity, @IdRes int id) {
        Intent intent = new Intent(activity, ListActivity.class);
        switch (id) {
            case R.id.menu_hero:
                intent.putExtra("type", 0);
                break;
            case R.id.menu_weapon:
                intent.putExtra("type", 1);
                break;
            case R.id.menu_skill:
                intent.putExtra("type", 2);
                break;
            default:
                intent.putExtra("type", 0);
        }
        activity.startActivity(intent);
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        int type = 0; // 0 - 英雄， 1 - 装备， 2 - 技能
        Intent intent = getIntent();
        if (intent != null ) {
            Bundle bundle = intent.getExtras();
            if (bundle != null) {
                type = bundle.getInt("type", 0);
            }
        }
        binding = DataBindingUtil.setContentView(this, R.layout.list_activity);
        handler = new ListHandler(this, binding, type);
        binding.setHandler(handler);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.toolbar_menu, menu);
        MenuItem menuItem = menu.findItem(R.id.menu_item_filter);
        handler.setMenuItem(menuItem);
        return super.onCreateOptionsMenu(menu);
    }

}
