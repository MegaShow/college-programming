package com.icytown.course.experimenttwo.receiver;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import com.icytown.course.experimenttwo.R;
import com.icytown.course.experimenttwo.data.model.FoodItem;
import com.icytown.course.experimenttwo.presentation.foodlist.FoodListActivity;

import java.util.Objects;

public class DynamicReceiver extends BroadcastReceiver {

    public static final String DYNAMIC_ACTION = "com.icytown.course.experimenttwo.action.DYNAMIC_ACTION";

    private static final String TAG = "DynamicReceiver";

    @Override
    public void onReceive(Context context, Intent intent) {
        if (Objects.requireNonNull(intent.getAction()).equals(DYNAMIC_ACTION)) {
            FoodItem item = intent.getParcelableExtra("food");
            int index = intent.getIntExtra("index", -1);
            NotificationManager manager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
            NotificationChannel channel = new NotificationChannel("channel", "通知", NotificationManager.IMPORTANCE_DEFAULT);
            manager.createNotificationChannel(channel);
            Notification.Builder builder = new Notification.Builder(context, channel.getId());
            Intent newIntent = new Intent(context, FoodListActivity.class);
            newIntent.putExtra("food", item);
            newIntent.putExtra("index", index);
            PendingIntent pendingIntent = PendingIntent.getActivity(context, 0, newIntent, PendingIntent.FLAG_UPDATE_CURRENT);
            Bitmap icon = BitmapFactory.decodeResource(context.getResources(), R.mipmap.sysu);
            builder.setContentTitle("已收藏")
                    .setContentText(item.getName())
                    .setTicker("已收藏:" + item.getName())
                    .setSmallIcon(R.drawable.empty_star)
                    .setLargeIcon(icon)
                    .setAutoCancel(true)
                    .setContentIntent(pendingIntent);
            manager.notify(1, builder.build());
        }
    }

    public static void sendDynamicAction(Context context, FoodItem item, int index) {
        Intent intent = new Intent(DYNAMIC_ACTION);
        intent.putExtra("food", item);
        intent.putExtra("index", index);
        context.sendBroadcast(intent);
    }
}
