package studio.xmatrix.qqpvp.assistant.ui.activity.search;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.drawable.Drawable;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Filter;
import android.widget.Filterable;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

import studio.xmatrix.qqpvp.assistant.R;

public class SearchAdapter extends BaseAdapter implements Filterable {

    private ArrayList<String> data;
    private String[] suggestions;
    private List<String> historySearch;
    private Drawable suggestionIcon;
    private LayoutInflater inflater;
    private boolean ellipsize;

    SearchAdapter(Context context, String[] suggestions) {
        inflater = LayoutInflater.from(context);
        data = new ArrayList<>();
        this.suggestions = suggestions;
        this.historySearch = new ArrayList<>();
    }

    SearchAdapter(Context context, String[] suggestions, Drawable suggestionIcon, boolean ellipsize) {
        inflater = LayoutInflater.from(context);
        data = new ArrayList<>();
        this.suggestions = suggestions;
        this.suggestionIcon = suggestionIcon;
        this.ellipsize = ellipsize;
    }

    @Override
    public Filter getFilter() {
        return new Filter() {
            @Override
            protected FilterResults performFiltering(CharSequence constraint) {
                FilterResults filterResults = new FilterResults();
                if (!TextUtils.isEmpty(constraint)) {

                    // Retrieve the autocomplete results.
                    List<String> searchData = new ArrayList<>();

                    for (String string : suggestions) {
                        if (string.substring(1).contains(constraint.toString())) {
                            searchData.add(string);
                        }
                    }

                    // Assign the data to the FilterResults
                    filterResults.values = searchData;
                    filterResults.count = searchData.size();
                } else {
                    // 添加默认推荐
                    List<String> searchData = new ArrayList<>();
                    searchData.add("1后羿");
                    searchData.add("2闪现");
                    searchData.add("3暗影战斧");
                    filterResults.values = searchData;
                    filterResults.count = searchData.size();
                }
                return filterResults;
            }

            @Override
            protected void publishResults(CharSequence constraint, FilterResults results) {
                if (results.values != null) {
                    data = (ArrayList<String>) results.values;
                    notifyDataSetChanged();
                }
            }
        };
    }

    @Override
    public int getCount() {
        return data.size();
    }

    @Override
    public Object getItem(int position) {
        return data.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @SuppressLint("SetTextI18n")
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {

        SuggestionsViewHolder viewHolder;

        if (convertView == null) {
            convertView = inflater.inflate(R.layout.search_suggestion_item, parent, false);
            viewHolder = new SuggestionsViewHolder(convertView);
            convertView.setTag(viewHolder);
        } else {
            viewHolder = (SuggestionsViewHolder) convertView.getTag();
        }

        String currentListData = (String) getItem(position);
        viewHolder.textView.setText(currentListData.substring(1));
        switch (currentListData.charAt(0)) {
            case '1':
                viewHolder.setIcon(convertView, R.drawable.ic_artifact);
                break;
            case '2':
                viewHolder.setIcon(convertView ,R.drawable.ic_skill);
                break;
            case '3':
            case '4':
                viewHolder.setIcon(convertView, R.drawable.ic_weapons);
                break;
        }
        if(currentListData.charAt(0) == '4') {
            viewHolder.textView.setText(currentListData.substring(1) + "(边境突围)");
        }
        if (ellipsize) {
            viewHolder.textView.setSingleLine();
            viewHolder.textView.setEllipsize(TextUtils.TruncateAt.END);
        }

        return convertView;
    }

    private class SuggestionsViewHolder {

        TextView textView;
        ImageView imageView;

        SuggestionsViewHolder(View convertView) {
            textView = convertView.findViewById(R.id.suggestion_text);
            if (suggestionIcon != null) {
                imageView = convertView.findViewById(R.id.suggestion_icon);
                imageView.setImageDrawable(suggestionIcon);
            }
        }

        void setIcon(View convertView, int icon) {
            imageView = convertView.findViewById(R.id.suggestion_icon);
            imageView.setImageResource(icon);
        }
    }
}