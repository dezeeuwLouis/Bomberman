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
    /// Logique d'interaction pour Login.xaml
    /// </summary>
    public partial class Login : Page
    {
        public MovieNet.Data.Facade Data = MovieNet.Data.Facade.Instance;

        public Login()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            // TODO
            // recupérer la valeur des champs de login
            // Envoyer une requete
            // en fonction du retour on redirige ou pas

            var usr = Data.Authenticate(loginInput.Text, passwordInput.Password);
            if (usr != null)
                this.NavigationService.Navigate(new HomePage());
            else
                errorContainer.Text = "Wrong email or password";
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Register());
        }
    }
}
