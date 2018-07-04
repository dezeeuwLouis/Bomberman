using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace MovieNet.UI
{
    /// <summary>
    /// Logique d'interaction pour HomePage.xaml
    /// </summary>
    public partial class HomePage : Page
    {
        public MovieNet.Data.Facade Data = MovieNet.Data.Facade.Instance;

        public HomePage()
        {
            InitializeComponent();

            filmList.ItemsSource = Data.getAllFimls().ToList();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Login());
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new CreateFilm());
        }

        private void filmList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            this.NavigationService.Navigate(new getFilm((Data.Film)filmList.SelectedItem));
            /*
            var clickedItem = (FrameworkElement)e.OriginalSource;
            Data.Film film = (Data.Film)clickedItem.DataContext;
            */
            // Data.RemoveMoovie((Data.Film)filmList.SelectedItem);
            // filmList.ItemsSource = Data.getAllFimls().ToList();
        }
    }
}
