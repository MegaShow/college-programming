package studio.xmatrix.qqpvp.assistant.inject.module;

import android.arch.lifecycle.ViewModelProvider;

import dagger.Binds;
import dagger.Module;
import dagger.multibindings.IntoMap;
import studio.xmatrix.qqpvp.assistant.inject.key.ViewModelKey;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModel;
import studio.xmatrix.qqpvp.assistant.ui.common.ViewModelFactory;

@Module
public abstract class ViewModelModule {

    @Binds
    @IntoMap
    @ViewModelKey(ViewModel.class)
    abstract android.arch.lifecycle.ViewModel bindListViewModel(ViewModel viewModel);


    @Binds
    abstract ViewModelProvider.Factory bindViewModelFactory(ViewModelFactory factory);
}
