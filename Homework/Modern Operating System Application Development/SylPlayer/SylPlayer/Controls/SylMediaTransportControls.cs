using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace SylPlayer.Controls {
    public sealed class SylMediaTransportControls : MediaTransportControls {
        public event EventHandler<EventArgs> FileOpenClick;
        public event EventHandler<EventArgs> PlayPauseClick;
        public event EventHandler<EventArgs> StopClick;

        public SylMediaTransportControls() {
            this.DefaultStyleKey = typeof(SylMediaTransportControls);
        }

        protected override void OnApplyTemplate() {
            var fileButton = GetTemplateChild("FileButton") as Button;
            var playPauseButton = GetTemplateChild("PlayPauseButton") as Button;
            var stopButton = GetTemplateChild("StopButton") as Button;
            fileButton.Click += FileButton_Click;
            playPauseButton.Click += PlayPauseButton_Click;
            stopButton.Click += StopButton_Click;
            base.OnApplyTemplate();
        }

        private void StopButton_Click(object sender, RoutedEventArgs e) {
            StopClick?.Invoke(this, EventArgs.Empty);
        }

        private void PlayPauseButton_Click(object sender, RoutedEventArgs e) {
            PlayPauseClick?.Invoke(this, EventArgs.Empty);
        }

        private void FileButton_Click(object sender, RoutedEventArgs e) {
            FileOpenClick?.Invoke(this, EventArgs.Empty);
        }
    }
}
