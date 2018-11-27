package studio.xmatrix.qqpvp.assistant.ui.activity.menu;

import android.view.View;

import studio.xmatrix.qqpvp.assistant.databinding.MenuActivityBinding;
import studio.xmatrix.qqpvp.assistant.ui.activity.collection.CollectionActivity;
import studio.xmatrix.qqpvp.assistant.ui.activity.list.ListActivity;
import studio.xmatrix.qqpvp.assistant.ui.activity.search.SearchActivity;

public class MenuHandler {
    private MenuActivity activity;
    private MenuActivityBinding binding;

    MenuHandler(MenuActivity activity, MenuActivityBinding binding) {
        this.activity = activity;
        this.binding = binding;
    }

    public void onClickList(View view) {
        ListActivity.startActivity(activity, view.getId());
    }

    public void onClickSearch(View view) {
        SearchActivity.startActivity(activity);
    }

    public void onClickCollection(View view) {
        CollectionActivity.startActivity(activity);
    }
}
