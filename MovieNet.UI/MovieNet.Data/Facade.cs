using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MovieNet.Data;

namespace MovieNet.Data
{
    public sealed class Facade
    {
        public static Facade instance = null;
        private Login LoginClass = null;
        private Moovie FilmClass = null;
        private DataModelContainer ctx = new DataModelContainer();

        public Facade()
        {
            LoginClass = new Login(ctx);
            FilmClass = new Moovie(ctx);
        }

        public static Facade Instance
        {
            get
            {
                if (instance == null)
                    instance = new Facade();
                return instance;
            }
    }

        public User Authenticate(String login, String password)
        {
            return LoginClass.Authenticate(login, password);
        }

        public User Register(String login, String password)
        {
            return LoginClass.Register(login, password);
        }

        public Film CreateMoovie(String name, String description, String resume)
        {
            return FilmClass.CreateMoovie(name, description, resume);
        }

        public IQueryable<Film> getAllFimls()
        {
            return FilmClass.getAllFimls();
        }

        public Boolean RemoveMoovie(Film film)
        {
            return FilmClass.RemoveMoovie(film);
        }
    
        public Boolean updateMoovie(Film film)
        {
            return FilmClass.updateMovie(film);
        }
    }
}
