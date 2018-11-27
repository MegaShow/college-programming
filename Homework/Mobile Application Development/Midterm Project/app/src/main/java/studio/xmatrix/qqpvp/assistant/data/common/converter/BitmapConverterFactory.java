package studio.xmatrix.qqpvp.assistant.data.common.converter;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import java.lang.annotation.Annotation;
import java.lang.reflect.Type;

import okhttp3.ResponseBody;
import retrofit2.Converter;
import retrofit2.Retrofit;

public final class BitmapConverterFactory extends Converter.Factory {

    private BitmapConverterFactory() {
    }

    public static BitmapConverterFactory create() {
        return new BitmapConverterFactory();
    }

    @Override
    public Converter<ResponseBody, Bitmap> responseBodyConverter(Type type, Annotation[] annotations, Retrofit retrofit) {
        if (type == Bitmap.class) {
            return value -> BitmapFactory.decodeStream(value.byteStream());
        } else {
            return null;
        }
    }
}