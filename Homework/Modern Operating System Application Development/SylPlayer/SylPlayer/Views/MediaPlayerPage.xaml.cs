using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using Windows.ApplicationModel.Core;
using Windows.Media.Core;
using Windows.Media.Playback;
using Windows.Storage;
using Windows.Storage.FileProperties;
using Windows.Storage.Pickers;
using Windows.System.Display;
using Windows.UI;
using Windows.UI.Core;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;

namespace SylPlayer.Views {
    public sealed partial class MediaPlayerPage : Page, INotifyPropertyChanged {
        private DisplayRequest _displayRequest = new DisplayRequest();
        private bool _isRequestActive = false;
        private bool _isPlay = false;

        public MediaPlayerPage() {
            InitializeComponent();
            CoreApplication.GetCurrentView().TitleBar.ExtendViewIntoTitleBar = true;
            ApplicationViewTitleBar titleBar = ApplicationView.GetForCurrentView().TitleBar;
            titleBar.ButtonBackgroundColor = Colors.Transparent;
            titleBar.ButtonInactiveBackgroundColor = Colors.Transparent;
        }

        protected override void OnNavigatedTo(NavigationEventArgs e) {
            base.OnNavigatedTo(e);
            mpe.MediaPlayer.PlaybackSession.PlaybackStateChanged += PlaybackSession_PlaybackStateChanged;
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e) {
            base.OnNavigatedFrom(e);
            mpe.MediaPlayer.Pause();
            mpe.MediaPlayer.PlaybackSession.PlaybackStateChanged -= PlaybackSession_PlaybackStateChanged;
        }

        private async void PlaybackSession_PlaybackStateChanged(MediaPlaybackSession sender, object args) {
            if (sender is MediaPlaybackSession playbackSession && playbackSession.NaturalVideoHeight != 0) {
                if (playbackSession.PlaybackState == MediaPlaybackState.Playing) {
                    if (!_isRequestActive) {
                        await Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () => {
                            _displayRequest.RequestActive();
                            _isRequestActive = true;
                        });
                    }
                } else {
                    if (_isRequestActive) {
                        await Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () => {
                            _displayRequest.RequestRelease();
                            _isRequestActive = false;
                        });
                    }
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void Set<T>(ref T storage, T value, [CallerMemberName]string propertyName = null) {
            if (Equals(storage, value)) {
                return;
            }

            storage = value;
            OnPropertyChanged(propertyName);
        }

        private void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));

        private async void SylMediaTransportControls_FileOpenClick(object sender, EventArgs e) {
            var openPicker = new FileOpenPicker();
            openPicker.FileTypeFilter.Add(".wmv");
            openPicker.FileTypeFilter.Add(".mp4");
            openPicker.FileTypeFilter.Add(".wma");
            openPicker.FileTypeFilter.Add(".mp3");
            StorageFile file = await openPicker.PickSingleFileAsync();
            if (file != null) {
                pictureRotate.Stop();
                mpe.Source = MediaSource.CreateFromStorageFile(file);
                mpe.MediaPlayer.Play();
                _isPlay = true;
                if (mpe.MediaPlayer.PlaybackSession.NaturalVideoHeight == 0) {
                    grid.Visibility = Windows.UI.Xaml.Visibility.Visible;
                    StorageItemThumbnail thumbnail = await file.GetThumbnailAsync(ThumbnailMode.SingleItem);
                    if (thumbnail == null) {
                        pictureImage.ImageSource = new BitmapImage(new Uri("ms-appx:///Assets/music.png"));
                    } else {
                        BitmapImage image = new BitmapImage();
                        image.SetSource(thumbnail);
                        pictureImage.ImageSource = image;
                    }
                    pictureRotate.Begin();
                } else {
                    grid.Visibility = Windows.UI.Xaml.Visibility.Collapsed;
                }
            }
        }

        private void SylMediaTransportControls_PlayPauseClick(object sender, EventArgs e) {
            if (grid.Visibility == Windows.UI.Xaml.Visibility.Visible) {
                if (_isPlay) {
                    _isPlay = false;
                    pictureRotate.Pause();
                } else {
                    _isPlay = true;
                    pictureRotate.Resume();
                }
            }
        }
    }
}
