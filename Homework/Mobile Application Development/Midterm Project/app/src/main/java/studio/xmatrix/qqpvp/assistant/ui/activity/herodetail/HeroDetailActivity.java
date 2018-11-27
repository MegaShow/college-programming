package studio.xmatrix.qqpvp.assistant.ui.activity.herodetail;

import android.app.Activity;
import android.content.Intent;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;

import java.util.Objects;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.databinding.DetailActivityBinding;

public class HeroDetailActivity extends AppCompatActivity {

    DetailActivityBinding binding;
    HeroDetailHandler handler;

    public static void startActivity(Activity activity, int id) {
        Intent intent = new Intent(activity, HeroDetailActivity.class);
        intent.putExtra("id", id);
        activity.startActivity(intent);
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.binding = DataBindingUtil.setContentView(this, R.layout.detail_activity);
        this.handler = new HeroDetailHandler(this, this.binding);
        Intent intent = getIntent();
        if (intent != null) {
            Bundle bundle = intent.getExtras();
            this.handler.initData(Objects.requireNonNull(bundle).getInt("id", 510));
        }
        binding.setHandler(new HeroDetailHandler(HeroDetailActivity.this, binding));
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.detail_menu, menu);
        MenuItem menuItemLove = menu.findItem(R.id.menu_item_love);
        MenuItem menuItemShare = menu.findItem(R.id.menu_item_share);
        handler.setMenuItemLove(menuItemLove);
        handler.setMenuItemShare(menuItemShare);
        return super.onCreateOptionsMenu(menu);
    }

}
