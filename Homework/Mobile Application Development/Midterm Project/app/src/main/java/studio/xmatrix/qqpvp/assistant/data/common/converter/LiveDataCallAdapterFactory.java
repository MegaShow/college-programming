package studio.xmatrix.qqpvp.assistant.data.common.converter;

import android.arch.lifecycle.LiveData;
import android.support.annotation.NonNull;

import java.lang.annotation.Annotation;
import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
import java.util.concurrent.atomic.AtomicBoolean;

import retrofit2.Call;
import retrofit2.CallAdapter;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import studio.xmatrix.qqpvp.assistant.data.common.ApiResponse;

public class LiveDataCallAdapterFactory extends CallAdapter.Factory {

    @Override
    public CallAdapter<?, ?> get(@NonNull Type returnType, @NonNull Annotation[] annotations, @NonNull Retrofit retrofit) {
        if (getRawType(returnType) != LiveData.class) {
            return null;
        }
        Type observableType = getParameterUpperBound(0, (ParameterizedType) returnType);
        Class<?> rawObservableType = getRawType(observableType);
        if (rawObservableType != ApiResponse.class) {
            throw new IllegalArgumentException("type must be a resource");
        }
        if (!(observableType instanceof ParameterizedType)) {
            throw new IllegalArgumentException("resource must be parameterized");
        }
        Type bodyType = getParameterUpperBound(0, (ParameterizedType) observableType);
        return new LiveDataCallAdapter<>(bodyType);
    }

    public static class LiveDataCallAdapter<R> implements CallAdapter<R, LiveData<ApiResponse<R>>> {

        private final Type responseType;

        LiveDataCallAdapter(Type responseType) {
            this.responseType = responseType;
        }

        @Override
        public Type responseType() {
            return responseType;
        }

        @Override
        public LiveData<ApiResponse<R>> adapt(@NonNull Call<R> call) {
            return new LiveData<ApiResponse<R>>() {
                AtomicBoolean started = new AtomicBoolean(false);

                @Override
                protected void onActive() {
                    super.onActive();
                    if (started.compareAndSet(false, true)) {
                        call.enqueue(new Callback<R>() {
                            @Override
                            public void onResponse(@NonNull Call<R> call, @NonNull Response<R> response) {
                                postValue(new ApiResponse<>(response));
                            }

                            @Override
                            public void onFailure(@NonNull Call<R> call, @NonNull Throwable throwable) {
                                postValue(new ApiResponse<>(throwable));
                            }
                        });
                    }
                }
            };
        }
    }
}
