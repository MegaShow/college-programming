package studio.xmatrix.qqpvp.assistant.ui.activity.menu;

import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.databinding.DataBindingUtil;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.widget.Toast;

import java.util.Calendar;
import java.util.Locale;

import studio.xmatrix.qqpvp.assistant.R;
import studio.xmatrix.qqpvp.assistant.databinding.MenuActivityBinding;
import studio.xmatrix.qqpvp.assistant.receiver.FreeNotification;

public class MenuActivity extends AppCompatActivity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        MenuActivityBinding binding = DataBindingUtil.setContentView(this, R.layout.menu_activity);
        binding.setHandler(new MenuHandler(this, binding));

        int permissionCheck = ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE);
        if(permissionCheck != PackageManager.PERMISSION_GRANTED) {
            requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 0);
        }

        if(FreeNotification.shouldNotify(this)) {
            startService(new Intent(this, FreeNotification.class));
            FreeNotification.updateDay(this);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if(requestCode != 0 ) return;
        if(grantResults.length == 0 ||
                grantResults[0] != PackageManager.PERMISSION_GRANTED &&
                ActivityCompat.shouldShowRequestPermissionRationale(this, permissions[0])){
            Toast.makeText(this, "您关闭了存储权限，将无法分享图片", Toast.LENGTH_SHORT).show();
        }
    }
}
