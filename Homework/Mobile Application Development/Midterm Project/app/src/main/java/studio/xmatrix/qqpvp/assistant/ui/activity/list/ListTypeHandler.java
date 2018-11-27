package studio.xmatrix.qqpvp.assistant.ui.activity.list;

import com.scwang.smartrefresh.layout.api.RefreshLayout;

public interface ListTypeHandler {
    void initList();
    void initView();
    void onClickFilter();
    void onRefresh(RefreshLayout refreshLayout);
}
