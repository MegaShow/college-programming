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
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;

namespace SylPlayer.Views {
    public sealed partial class BadMediaPlayerPage : Page, INotifyPropertyChanged {
        private DisplayRequest _displayRequest = new DisplayRequest();
        private bool _isRequestActive = false;
        private bool _isPlay = false;
        private bool _isStop = true;
        private DispatcherTimer dispatcher;

        private double oldVolume = 0;
        private double volume {
            get { return mpe.MediaPlayer.Volume * 100; }
            set { mpe.MediaPlayer.Volume = value / 100; }
        }

        public BadMediaPlayerPage() {
            InitializeComponent();
            CoreApplication.GetCurrentView().TitleBar.ExtendViewIntoTitleBar = true;
            ApplicationViewTitleBar titleBar = ApplicationView.GetForCurrentView().TitleBar;
            titleBar.ButtonBackgroundColor = Colors.Transparent;
            titleBar.ButtonInactiveBackgroundColor = Colors.Transparent;
            mpe.MediaPlayer.MediaOpened += MediaOpened;
            mpe.MediaPlayer.MediaEnded += MediaEnded;
            dispatcher = new DispatcherTimer();
            dispatcher.Interval = new TimeSpan(0, 0, 1);
            dispatcher.Tick += PositionChanged;
            UpdateVolumeIcon();
        }

        private void PositionChanged(object sender, object e) {
            TimeSpan timeSpanLeft = mpe.MediaPlayer.PlaybackSession.Position;
            TimeSpan timeSpanRight = mpe.MediaPlayer.PlaybackSession.NaturalDuration - timeSpanLeft;
            leftTime.Text = timeSpanLeft.ToString(@"hh\:mm\:ss");
            rightTime.Text = timeSpanRight.ToString(@"hh\:mm\:ss");
            PositionSlider.Value = mpe.MediaPlayer.PlaybackSession.Position.TotalSeconds;
        }

        private async void MediaOpened(MediaPlayer sender, object args) {
            await Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () => {
                PositionSlider.Maximum = mpe.MediaPlayer.PlaybackSession.NaturalDuration.TotalSeconds;
                dispatcher.Start();
            });
        }

        private async void MediaEnded(MediaPlayer sender, object args) {
            await Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () => {
                dispatcher.Stop();
                leftTime.Text = "0:00:00";
                rightTime.Text = "0:00:00";
                PositionSlider.Value = 0;
                _isPlay = false;
                _isStop = true;
                PlayPauseButton.Icon = new SymbolIcon(Symbol.Play);
                StopButton.IsEnabled = false;
                if (grid.Visibility == Visibility.Visible) {
                    pictureRotate.Stop();
                }
            });
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

        private void Slider_ValueChanged(object sender, Windows.UI.Xaml.Controls.Primitives.RangeBaseValueChangedEventArgs e) {
            mpe.MediaPlayer.PlaybackSession.Position = TimeSpan.FromSeconds(e.NewValue);
        }

        private async void FileOpenButton_Click(object sender, RoutedEventArgs e) {
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
                _isStop = false;
                if (mpe.MediaPlayer.PlaybackSession.NaturalVideoHeight == 0) {
                    grid.Visibility = Visibility.Visible;
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
                    grid.Visibility = Visibility.Collapsed;
                }
                PlayPauseButton.Icon = new SymbolIcon(Symbol.Pause);
                PlayPauseButton.IsEnabled = true;
                StopButton.IsEnabled = true;
            }
        }

        private void PlayPauseButton_Click(object sender, RoutedEventArgs e) {
            if (_isStop == true) {
                PlayPauseButton.Icon = new SymbolIcon(Symbol.Pause);
                StopButton.IsEnabled = true;
                _isStop = false;
                _isPlay = true;
                mpe.MediaPlayer.Play();
                if (grid.Visibility == Visibility.Visible) {
                    pictureRotate.Begin();
                }
            } else if (_isPlay == true) {
                PlayPauseButton.Icon = new SymbolIcon(Symbol.Play);
                _isPlay = false;
                mpe.MediaPlayer.Pause();
                if (grid.Visibility == Visibility.Visible) {
                    pictureRotate.Pause();
                }
            } else if (_isPlay == false) {
                PlayPauseButton.Icon = new SymbolIcon(Symbol.Pause);
                _isPlay = true;
                mpe.MediaPlayer.Play();
                if (grid.Visibility == Visibility.Visible) {
                    pictureRotate.Resume();
                }
            }
        }

        private void StopButton_Click(object sender, RoutedEventArgs e) {
            PlayPauseButton.Icon = new SymbolIcon(Symbol.Play);
            StopButton.IsEnabled = false;
            _isStop = true;
            _isPlay = false;
            mpe.MediaPlayer.Pause();
            mpe.MediaPlayer.PlaybackSession.Position = new TimeSpan(0);
            if (grid.Visibility == Visibility.Visible) {
                pictureRotate.Stop();
            }
            if (grid.Visibility == Visibility.Visible) {
                pictureRotate.Stop();
            }
        }

        private void AudioMuteButton_Click(object sender, RoutedEventArgs e) {
            if (volume == 0) {
                volume = oldVolume;
            } else {
                oldVolume = volume;
                volume = 0;
            }
            UpdateVolumeIcon();
            OnPropertyChanged("volume");
        }

        private void VolumeSlider_ValueChanged(object sender, Windows.UI.Xaml.Controls.Primitives.RangeBaseValueChangedEventArgs e) {
            UpdateVolumeIcon();
        }

        private void UpdateVolumeIcon() {
            if (VolumeSlider.Value == 0) {
                AudioMuteButton.Icon = new SymbolIcon(Symbol.Mute);
                VolumeMuteButton.Icon = new SymbolIcon(Symbol.Mute);
            } else {
                AudioMuteButton.Icon = new SymbolIcon(Symbol.Volume);
                VolumeMuteButton.Icon = new SymbolIcon(Symbol.Volume);
            }
        }

        private void FullWindowButton_Click(object sender, RoutedEventArgs e) {
            if (ApplicationView.GetForCurrentView().IsFullScreenMode) {
                ApplicationView.GetForCurrentView().ExitFullScreenMode();
                titleRow.Height = new GridLength(32);
            } else {
                ApplicationView.GetForCurrentView().TryEnterFullScreenMode();
                titleRow.Height = new GridLength(0);
            }
        }
    }
}
