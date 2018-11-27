package studio.xmatrix.qqpvp.assistant.data.service;

import android.arch.lifecycle.LiveData;
import android.arch.lifecycle.MutableLiveData;

import org.jsoup.HttpStatusException;
import org.jsoup.Jsoup;
import org.jsoup.UnsupportedMimeTypeException;
import org.jsoup.nodes.Document;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.SocketTimeoutException;

import javax.inject.Inject;
import javax.inject.Singleton;

import studio.xmatrix.qqpvp.assistant.data.common.AppExecutors;
import studio.xmatrix.qqpvp.assistant.data.common.JsoupResponse;

@Singleton
public class DataHtmlService {

    private AppExecutors executors;

    private static final String BASE_URL = "http://pvp.qq.com/web201605/herodetail/";

    @Inject
    public DataHtmlService(AppExecutors executors) {
        this.executors = executors;
    }

    public LiveData<JsoupResponse<Document>> getHeroDetail(int id) {
        final String url = BASE_URL + id + ".shtml";
        MutableLiveData<JsoupResponse<Document>> data = new MutableLiveData<>();
        executors.networkIO().execute(() -> {
            try {
                Document document = Jsoup.connect(url).get();
                data.postValue(new JsoupResponse<>(document));
            } catch (MalformedURLException e) {
                Throwable error = new Throwable("the request URL is not a HTTP or HTTPS URL, or is otherwise malformed");
                data.postValue(new JsoupResponse<>(error));
            } catch (HttpStatusException e) {
                Throwable error = new Throwable("the response is not OK and HTTP response errors are not ignored");
                data.postValue(new JsoupResponse<>(error));
            } catch (UnsupportedMimeTypeException e) {
                Throwable error = new Throwable("the response mime type is not supported and those errors are not ignored");
                data.postValue(new JsoupResponse<>(error));
            } catch (SocketTimeoutException e) {
                Throwable error = new Throwable("the connection times out");
                data.postValue(new JsoupResponse<>(error));
            } catch (IOException e) {
                data.postValue(new JsoupResponse<>(e));
            }
        });
        return data;
    }
}
