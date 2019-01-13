package com.icytown.course.experimenttwo.receiver;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import com.icytown.course.experimenttwo.R;
import com.icytown.course.experimenttwo.data.model.FoodItem;
import com.icytown.course.experimenttwo.presentation.fooddetail.FoodDetailActivity;

import java.util.Objects;

public class StaticReceiver extends BroadcastReceiver {

    public static final String STATIC_ACTION = "com.icytown.course.experimenttwo.action.STATIC_ACTION";

    private static final String TAG = "StaticReceiver";

    @Override
    public void onReceive(Context context, Intent intent) {
        if (Objects.requireNonNull(intent.getAction()).equals(STATIC_ACTION)) {
            FoodItem item = intent.getParcelableExtra("food");
            int index = intent.getIntExtra("index", -1);
            NotificationManager manager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
            NotificationChannel channel = new NotificationChannel("channel", "通知", NotificationManager.IMPORTANCE_DEFAULT);
            manager.createNotificationChannel(channel);
            Notification.Builder builder = new Notification.Builder(context, channel.getId());
            Intent newIntent = new Intent(context, FoodDetailActivity.class);
            newIntent.putExtra("food", item);
            newIntent.putExtra("index", index);
            PendingIntent pendingIntent = PendingIntent.getActivity(context, 0, newIntent, PendingIntent.FLAG_UPDATE_CURRENT);
            Bitmap icon = BitmapFactory.decodeResource(context.getResources(), R.mipmap.sysu);
            builder.setContentTitle("今日推荐")
                    .setContentText(item.getName())
                    .setTicker("今日推荐:" + item.getName())
                    .setSmallIcon(R.drawable.empty_star)
                    .setLargeIcon(icon)
                    .setAutoCancel(true)
                    .setContentIntent(pendingIntent);
            manager.notify(0, builder.build());
        }
    }

    public static void sendStaticAction(Context context, FoodItem item, int index) {
        Intent intent = new Intent(STATIC_ACTION);
        intent.setComponent(new ComponentName(context, context.getPackageName() + ".receiver." + TAG));
        intent.putExtra("food", item);
        intent.putExtra("index", index);
        context.sendBroadcast(intent);
    }
}
