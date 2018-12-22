package com.icytown.course.experimentfive.webapi.ui.bilibili

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.databinding.DataBindingUtil
import androidx.recyclerview.widget.RecyclerView
import com.icytown.course.experimentfive.webapi.R
import com.icytown.course.experimentfive.webapi.data.service.BilibiliApiService
import com.icytown.course.experimentfive.webapi.data.model.Top
import com.icytown.course.experimentfive.webapi.databinding.BilibiliItemBinding
import io.reactivex.rxkotlin.subscribeBy

class RecyclerViewAdapter : RecyclerView.Adapter<RecyclerViewAdapter.BindingHolder>() {

    val items = ArrayList<Top>()

    fun add(top: Top) {
        items += top
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): BindingHolder {
        val binding = DataBindingUtil.inflate<BilibiliItemBinding>(
            LayoutInflater.from(parent.context),
            R.layout.bilibili_item,
            parent,
            false
        )
        val holder =
            BindingHolder(binding.root)
        holder.binding = binding
        return holder
    }

    override fun onBindViewHolder(holder: BindingHolder, position: Int) {
        holder.binding.model = items[position]
        holder.binding.presenter = BilibiliPresenter(holder.binding)
        holder.binding.executePendingBindings()
        items[position].data?.run {
            holder.binding.seekBar.isEnabled = false
            BilibiliApiService.getBitmap(this.cover).subscribeBy(
                onNext = {
                    holder.binding.presenter?.cover = it
                    holder.binding.imageView.setImageBitmap(it)
                    holder.binding.progressBar.visibility = View.GONE
                },
                onError = {}
            )
            BilibiliApiService.getPVideo(this.aid).subscribeBy(
                onNext = { it ->
                    holder.binding.pvideo = it
                    if (it.data != null) {
                        holder.binding.seekBar.max = it.data.indices.size
                        holder.binding.presenter?.images = Array(it.data.images.size) { null }
                        for (i in 0 until it.data.images.size) {
                            BilibiliApiService.getBitmap(it.data.images[i]).subscribeBy(
                                onNext = {
                                    holder.binding.seekBar.isEnabled = true
                                    holder.binding.presenter?.images?.set(i, it)
                                },
                                onError = {}
                            )
                        }
                    }
                },
                onError = {}
            )
            return
        }
    }

    override fun getItemCount(): Int {
        return items.size
    }

    class BindingHolder(view: View) : RecyclerView.ViewHolder(view) {
        lateinit var binding: BilibiliItemBinding
    }
}
