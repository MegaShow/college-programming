package studio.xmatrix.qqpvp.assistant.receiver;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Binder;
import android.os.IBinder;
import android.os.SystemClock;
import android.support.annotation.Nullable;

import java.util.Calendar;
import java.util.Set;

import studio.xmatrix.qqpvp.assistant.R;

public class FreeNotification extends Service {
    private final IBinder binder = new FreeBinder();

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        //return null;
        return binder;
    }

    @Override
    public void onCreate() {
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        AlarmManager manager = (AlarmManager) getSystemService(ALARM_SERVICE);
        int interval = 24*60*60*1000;
        long firstTime = SystemClock.elapsedRealtime() + 5000;
        Intent i = new Intent(this, AlarmReceiver.class);
        PendingIntent pi = PendingIntent.getBroadcast(this, 0, i, 0);
        manager.setRepeating(AlarmManager.ELAPSED_REALTIME_WAKEUP, firstTime, interval, pi);
        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    private static int getWeek() {
        Calendar calendar = Calendar.getInstance();
        int thisweek = calendar.get(Calendar.WEEK_OF_MONTH);
        int thisday = calendar.get(Calendar.DAY_OF_WEEK);
        if(thisday == Calendar.SUNDAY) return thisweek - 1;
        return thisweek;
    }

    public static int getWeekDay() {
        Calendar calendar = Calendar.getInstance();
        return calendar.get(Calendar.DAY_OF_WEEK);
    }

    public static boolean shouldNotify(Context context) {
        SharedPreferences sharedPreferences = context.getSharedPreferences(
                context.getString(R.string.preference), Context.MODE_PRIVATE);
        int lastday = sharedPreferences.getInt("day", -1);
        int thisday = Calendar.getInstance().get(Calendar.DAY_OF_YEAR);
        return lastday != thisday && isUpdated(context);
    }

    public static boolean isUpdated(Context context) {
        SharedPreferences sharedPreferences = context.getSharedPreferences(
                context.getString(R.string.preference), Context.MODE_PRIVATE);
        int lastweek = sharedPreferences.getInt("freeweek", -1);
        int thisweek = getWeek();
        return lastweek == thisweek;
    }

    public static void updateDay(Context context) {
        SharedPreferences sharedPreferences = context.getSharedPreferences(
                context.getString(R.string.preference), Context.MODE_PRIVATE);
        int thisday = Calendar.getInstance().get(Calendar.DAY_OF_YEAR);
        sharedPreferences.edit().putInt("day", thisday).commit();
    }

    public static void updateFreeHero(Context context, Set<String> freehero) {
        SharedPreferences sharedPreferences = context.getSharedPreferences(
                context.getString(R.string.preference), Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putStringSet("freehero", freehero);
        int thisweek = getWeek();
        editor.putInt("freeweek", thisweek).commit();
    }

    public class FreeBinder extends Binder {
        FreeNotification getService() {
            return FreeNotification.this;
        }
    }
}
