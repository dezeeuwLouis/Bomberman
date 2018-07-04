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
    /// Logique d'interaction pour getFilm.xaml
    /// </summary>
    public partial class getFilm : Page
    {
        Data.Film myFilm = null;
        public MovieNet.Data.Facade Data = MovieNet.Data.Facade.Instance;

        public getFilm(Data.Film film)
        {
            InitializeComponent();

            myFilm = film;
            nameInp.Text = film.name;
            categoryInp.Text = "Horror";
            resumeInp.Text = film.description;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Data.Film film = new Data.Film();

            film.Id = myFilm.Id;
            film.name = nameInp.Text;
            film.description = resumeInp.Text;

            Data.updateMoovie(film);
        }
    }
}
