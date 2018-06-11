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
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MovieNet.Data.Facade Data = MovieNet.Data.Facade.Instance;

        public MainWindow()
        {
            bool isLogged = Data.IsLogged();

            InitializeComponent();

            if (isLogged)
                Main.Content = new HomePage();
            else
                Main.Content = new Login();
        }
    }
}
