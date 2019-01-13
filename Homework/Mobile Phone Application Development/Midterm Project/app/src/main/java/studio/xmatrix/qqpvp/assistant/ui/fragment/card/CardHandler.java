package studio.xmatrix.qqpvp.assistant.ui.fragment.card;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.net.Uri;
import android.provider.MediaStore;
import android.support.v4.content.ContextCompat;
import android.support.v4.content.FileProvider;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.view.View;

import java.io.File;

import studio.xmatrix.qqpvp.assistant.BuildConfig;
import studio.xmatrix.qqpvp.assistant.databinding.ItemCardBinding;

public class CardHandler {

    private CardFragment fragment;
    private Activity activity;
    private ItemCardBinding binding;
    private onClickCardLike onClickCardLike;

    public void setOnClickCardLike(CardHandler.onClickCardLike onClickCardLike) {
        this.onClickCardLike = onClickCardLike;
    }

    public interface onClickCardLike {
        void onClick(View v);
    }

    CardHandler(CardFragment fragment,ItemCardBinding binding, AppCompatActivity activity) {
        this.fragment = fragment;
        this.activity = activity;
        this.binding = binding;
    }

    public void onClickOk(View v) {
        fragment.dismiss();
    }

    // 点击收藏
    public void onClickLike(View v) {
        onClickCardLike.onClick(v);
    }

    // 点击分享
    public void onClickShare(View v) {
        share(fragment.getView());
    }

    private void share(View v) {
        Uri uri = createShareFile(v, activity);
        Intent intent = new Intent(Intent.ACTION_SEND);
        if(uri == null) {
            intent.setType("text/plain");
            String text;
            if (binding.itemCardAttrPic.getVisibility() == View.VISIBLE) {
                String url = "http://pvp.qq.com/web201605/summoner.shtml";
                text = "向你推荐王者荣耀召唤师技能【" + binding.itemCardName.getText() + "】，详见：" + url;
            } else {
                String url = "http://pvp.qq.com/web201605/item.shtml";
                text = "向你推荐王者荣耀道具【" + binding.itemCardName.getText() + "】，详见：" + url;
            }
            intent.putExtra(Intent.EXTRA_TEXT, text);
            activity.startActivity(Intent.createChooser(intent, "分享"));
        }
        else {
            intent.setType("image/*");
            intent.putExtra(Intent.EXTRA_STREAM, uri);
            activity.startActivity(Intent.createChooser(intent, "分享"));
        }
    }

    public static Uri createShareFile(View v, Activity activity) {
        if(!checkWritePermission(activity)) return null;

        Bitmap bitmap = Bitmap.createBitmap(v.getMeasuredWidth(), v.getMeasuredHeight(), Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(bitmap);
        v.layout(v.getLeft(), v.getTop(), v.getRight(), v.getBottom());
        v.draw(canvas);
        bitmap = Bitmap.createBitmap(bitmap, 0, 5, v.getMeasuredWidth(), v.getMeasuredHeight() - 223);

        String filePath;
        filePath = MediaStore.Images.Media.insertImage(activity.getContentResolver(), bitmap, null, null);

        if (!bitmap.isRecycled()) {
            bitmap.recycle();
        }
        if (TextUtils.isEmpty(filePath)) {
            return null;
        }

        filePath = getRealPathFromURI(activity.getApplicationContext(), Uri.parse(filePath));
        File file = new File(filePath);
        return FileProvider.getUriForFile(activity.getApplicationContext(),
                BuildConfig.APPLICATION_ID + ".fileProvider", file);
    }

    private static boolean checkWritePermission(Activity activity) {
        int permissionCheck = ContextCompat.checkSelfPermission(activity, Manifest.permission.WRITE_EXTERNAL_STORAGE);
        return permissionCheck == PackageManager.PERMISSION_GRANTED;
    }

    private static String getRealPathFromURI(Context context, Uri contentUri) {
        String[] proj = {MediaStore.Images.Media.DATA};
        try (Cursor cursor = context.getContentResolver().query(contentUri, proj, null, null, null)) {
            if (cursor == null) {
                return "";
            }
            int column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
            cursor.moveToFirst();
            return cursor.getString(column_index);
        }
    }
}
