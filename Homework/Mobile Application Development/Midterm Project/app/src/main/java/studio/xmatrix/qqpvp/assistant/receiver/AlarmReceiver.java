package studio.xmatrix.qqpvp.assistant.receiver;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.util.ArraySet;

import java.util.ArrayList;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.ui.activity.herodetail.HeroDetailActivity;

public class AlarmReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        if(!FreeNotification.isUpdated(context)) return;
        SharedPreferences sharedPreferences = context.getSharedPreferences(
                context.getString(R.string.preference), Context.MODE_PRIVATE);
        ArrayList<String> freehero = new ArrayList<>(sharedPreferences.getStringSet("freehero", new ArraySet<>()));
        if(freehero.isEmpty()) return;

        String channelID = "free";
        String channelName = "FreeChannel";
        NotificationChannel channel = new NotificationChannel(channelID,
                channelName, NotificationManager.IMPORTANCE_HIGH);
        NotificationManager manager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        manager.createNotificationChannel(channel);
        Notification.Builder builder = new Notification.Builder(context, channelID);

        int day = FreeNotification.getWeekDay() - 1;
        String hero = freehero.get(day);
        String[] heroAttr = hero.split(",");
        String heroID = heroAttr[0];
        String heroName = heroAttr[1];
        Intent contentIntent = new Intent(context, HeroDetailActivity.class);
        Bundle bundle = new Bundle();
        bundle.putInt("id", Integer.valueOf(heroID));
        contentIntent.putExtras(bundle);
        PendingIntent pendingIntent = PendingIntent.getActivity(context, 0,
                contentIntent, PendingIntent.FLAG_CANCEL_CURRENT);
        builder.setSmallIcon(R.mipmap.ic_launcher)
                .setTicker("周免英雄推荐")
                .setContentTitle(heroName)
                .setContentText("点击查看该周免英雄详情")
                .setContentIntent(pendingIntent)
                .setAutoCancel(true);
        Notification notification = builder.build();
        manager.notify((int)System.currentTimeMillis(),notification);
        FreeNotification.updateDay(context);
    }
}
