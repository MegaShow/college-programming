package studio.xmatrix.qqpvp.assistant.data.common.converter;

import com.google.gson.TypeAdapter;
import com.google.gson.stream.JsonReader;
import com.google.gson.stream.JsonToken;
import com.google.gson.stream.JsonWriter;

import java.io.IOException;

import studio.xmatrix.qqpvp.assistant.data.model.apimodel.ApiHeroListItem;

public class PayTypeAdapter extends TypeAdapter<ApiHeroListItem.PayType> {

    @Override
    public ApiHeroListItem.PayType read(JsonReader in) throws IOException {
        if (in.peek() == JsonToken.NULL) {
            in.nextNull();
            return null;
        }
        ApiHeroListItem.PayType data = new ApiHeroListItem.PayType();
        if (in.peek() == JsonToken.NUMBER) {
            data.ctx = String.valueOf(in.nextInt());
        } else if (in.peek() == JsonToken.STRING) {
            data.ctx = in.nextString();
        }
        return data;
    }

    @Override
    public void write(JsonWriter out, ApiHeroListItem.PayType value) throws IOException {
        out.nullValue();
    }
}
