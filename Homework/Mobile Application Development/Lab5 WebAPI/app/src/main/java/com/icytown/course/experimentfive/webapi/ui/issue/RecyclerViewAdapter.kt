package com.icytown.course.experimentfive.webapi.ui.issue

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import androidx.recyclerview.widget.RecyclerView
import com.icytown.course.experimentfive.webapi.R
import com.icytown.course.experimentfive.webapi.data.model.Issue
import com.icytown.course.experimentfive.webapi.databinding.IssueItemBinding

class RecyclerViewAdapter : RecyclerView.Adapter<RecyclerViewAdapter.BindingHolder>() {

    var items: List<Issue> = ArrayList()

    fun reset(list: List<Issue>) {
        items = list
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): BindingHolder {
        val binding = DataBindingUtil.inflate<IssueItemBinding>(
            LayoutInflater.from(parent.context),
            R.layout.issue_item,
            parent,
            false
        )
        val holder = BindingHolder(binding.root)
        holder.binding = binding
        return holder
    }

    override fun onBindViewHolder(holder: BindingHolder, position: Int) {
        holder.binding.model = items[position]
        holder.binding.executePendingBindings()
    }

    override fun getItemCount(): Int {
        return items.size
    }

    class BindingHolder(view: View) : RecyclerView.ViewHolder(view) {
        lateinit var binding: IssueItemBinding
    }
}
