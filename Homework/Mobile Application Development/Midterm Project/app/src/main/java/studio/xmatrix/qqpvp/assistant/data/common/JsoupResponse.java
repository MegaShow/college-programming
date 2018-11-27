package studio.xmatrix.qqpvp.assistant.data.common;

import android.support.annotation.Nullable;

public class JsoupResponse<T> {

    public final int code;
    @Nullable
    public final T body;
    @Nullable
    public final String errorMessage;

    public JsoupResponse(Throwable error) {
        code = 500;
        body = null;
        errorMessage = error.getMessage();
    }

    public JsoupResponse(T t) {
        code = 200;
        body = t;
        errorMessage = "";
    }

    public boolean isSuccessful() {
        return code == 200;
    }
}
