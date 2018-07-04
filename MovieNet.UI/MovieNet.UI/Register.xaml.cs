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
    /// Logique d'interaction pour Register.xaml
    /// </summary>
    public partial class Register : Page
    {
        public MovieNet.Data.Facade Data = MovieNet.Data.Facade.Instance;
        public Register()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (passwordInput.Password == confirmInput.Password)
            {
                var usr = Data.Register(loginInput.Text, passwordInput.Password);
                if (usr == null)
                    errorContainer.Text = "An error occured";
                else
                    this.NavigationService.Navigate(new Login());
            }
            else
                errorContainer.Text = "You typed two different password";
        }
    }
}
