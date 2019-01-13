package com.icytown.course.experimenttwo.receiver;

import android.app.PendingIntent;
import android.appwidget.AppWidgetManager;
import android.appwidget.AppWidgetProvider;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.widget.RemoteViews;

import com.icytown.course.experimenttwo.R;
import com.icytown.course.experimenttwo.data.model.FoodItem;
import com.icytown.course.experimenttwo.presentation.fooddetail.FoodDetailActivity;
import com.icytown.course.experimenttwo.presentation.foodlist.FoodListActivity;

import java.util.Objects;

public class WidgetProvider extends AppWidgetProvider {

    public static final String STATIC_ACTION = "com.icytown.course.experimenttwo.action.STATIC_ACTION";
    public static final String DYNAMIC_ACTION = "com.icytown.course.experimenttwo.action.DYNAMIC_ACTION";

    private static final String TAG = "WidgetProvider";

    static void updateAppWidget(Context context, AppWidgetManager appWidgetManager, int[] appWidgetIds, String msg, PendingIntent intent) {
        RemoteViews views = new RemoteViews(context.getPackageName(), R.layout.app_widget);
        views.setTextViewText(R.id.appwidget_text, msg);
        views.setOnClickPendingIntent(R.id.appwidget_layout, intent);
        appWidgetManager.updateAppWidget(appWidgetIds, views);
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        super.onReceive(context, intent);
        ComponentName name = new ComponentName(context, context.getPackageName() + ".receiver." + TAG);
        int[] appWidgetIds = AppWidgetManager.getInstance(context).getAppWidgetIds(name);
        int index = intent.getIntExtra("index", -1);
        FoodItem item = intent.getParcelableExtra("food");
        if (Objects.requireNonNull(intent.getAction()).equals(STATIC_ACTION)) {
            Intent i = new Intent(context, FoodDetailActivity.class);
            i.putExtra("food", item);
            i.putExtra("index", index);
            PendingIntent pendingIntent = PendingIntent.getActivity(context, 0, i, PendingIntent.FLAG_UPDATE_CURRENT);
            updateAppWidget(context, AppWidgetManager.getInstance(context), appWidgetIds, "今日推荐 " + item.getName(), pendingIntent);
        } else if (Objects.requireNonNull(intent.getAction()).equals(DYNAMIC_ACTION)) {
            Intent i = new Intent(context, FoodListActivity.class);
            i.putExtra("food", item);
            i.putExtra("index", index);
            PendingIntent pendingIntent = PendingIntent.getActivity(context, 0, i, PendingIntent.FLAG_UPDATE_CURRENT);
            updateAppWidget(context, AppWidgetManager.getInstance(context), appWidgetIds, "已收藏 " + item.getName(), pendingIntent);
        }
    }

    @Override
    public void onUpdate(Context context, AppWidgetManager appWidgetManager, int[] appWidgetIds) {
        Intent i = new Intent(context, FoodListActivity.class);
        PendingIntent pendingIntent = PendingIntent.getActivity(context, 0, i, PendingIntent.FLAG_UPDATE_CURRENT);
        updateAppWidget(context, appWidgetManager, appWidgetIds, context.getString(R.string.appwidget_text), pendingIntent);
    }

    public static void sendStaticAction(Context context, FoodItem item, int index) {
        ComponentName name = new ComponentName(context, context.getPackageName() + ".receiver." + TAG);
        Intent intent = new Intent(STATIC_ACTION);
        intent.setComponent(name);
        intent.putExtra("food", item);
        intent.putExtra("index", index);
        context.sendBroadcast(intent);
    }

    public static void sendDynamicAction(Context context, FoodItem item, int index) {
        Intent intent = new Intent(DYNAMIC_ACTION);
        intent.putExtra("food", item);
        intent.putExtra("index", index);
        context.sendBroadcast(intent);
    }
}
