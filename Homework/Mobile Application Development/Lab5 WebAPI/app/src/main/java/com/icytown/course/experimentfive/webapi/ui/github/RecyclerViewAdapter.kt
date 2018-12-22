package com.icytown.course.experimentfive.webapi.ui.github

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import androidx.recyclerview.widget.RecyclerView
import com.icytown.course.experimentfive.webapi.R
import com.icytown.course.experimentfive.webapi.data.model.Repository
import com.icytown.course.experimentfive.webapi.databinding.GithubItemBinding

class RecyclerViewAdapter : RecyclerView.Adapter<RecyclerViewAdapter.BindingHolder>() {

    lateinit var owner: String
    var items: List<Repository> = ArrayList()

    fun reset(owner: String, items: List<Repository>) {
        this.owner = owner
        this.items = items
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): BindingHolder {
        val binding = DataBindingUtil.inflate<GithubItemBinding>(
            LayoutInflater.from(parent.context),
            R.layout.github_item,
            parent,
            false
        )
        val holder = BindingHolder(binding.root)
        holder.binding = binding
        return holder
    }

    override fun onBindViewHolder(holder: BindingHolder, position: Int) {
        holder.binding.owner = owner
        holder.binding.model = items[position]
        holder.binding.presenter = GithubPresenter
        holder.binding.executePendingBindings()
    }

    override fun getItemCount(): Int {
        return items.size
    }

    class BindingHolder(view: View) : RecyclerView.ViewHolder(view) {
        lateinit var binding: GithubItemBinding
    }
}
