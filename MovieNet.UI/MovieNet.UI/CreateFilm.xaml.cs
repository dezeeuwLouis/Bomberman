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
    /// Logique d'interaction pour CreateFilm.xaml
    /// </summary>
    public partial class CreateFilm : Page
    {
        public MovieNet.Data.Facade Data = MovieNet.Data.Facade.Instance;

        public CreateFilm()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var film = Data.CreateMoovie(nameInp.Text, categoryInp.Text, resumeInp.Text);
            if (film != null)
                this.NavigationService.Navigate(new HomePage());
        }
    }
}
