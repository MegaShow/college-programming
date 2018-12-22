package com.icytown.course.experimentfive.webapi.ui.bilibili

import android.graphics.Bitmap
import android.widget.SeekBar
import com.icytown.course.experimentfive.webapi.databinding.BilibiliItemBinding

class BilibiliPresenter(val binding: BilibiliItemBinding) {

    lateinit var cover: Bitmap
    lateinit var images: Array<Bitmap?>

    fun onProgressChanged(seekBar: SeekBar, progress: Int, fromUser: Boolean) {
        if (fromUser) {
            binding.pvideo?.data?.let { it ->
                val imageIndex = progress / (it.xLen * it.yLen)
                val xIndex = progress % (it.xLen * it.yLen) % it.xLen
                val yIndex = progress % (it.xLen * it.yLen) / it.yLen
                images[imageIndex]?.let { bitmap ->
                    binding.imageView.setImageBitmap(
                        Bitmap.createBitmap(
                            bitmap,
                            xIndex * it.xSize,
                            yIndex * it.ySize,
                            it.xSize,
                            it.ySize
                        )
                    )
                }
            }
        }
    }

    fun onStopTrackingTouch(seekBar: SeekBar) {
        binding.imageView.setImageBitmap(cover)
        binding.seekBar.progress = 0
    }
}