using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MovieNet.Data
{
    class Moovie
    {
        DataModelContainer ctx = null;

        public Moovie(DataModelContainer context)
        {
            ctx = context;
        }

        public IQueryable<Film> getAllFimls()
        {
            return ctx.Set<Film>();
        }

        public Film CreateMoovie(String name, String genre, String resume)
        {
            Film film = new Film();

            // film.genre = genre;
            film.name = name;
            film.description = resume;
            ctx.FilmSet.Add(film);
            ctx.SaveChanges();

            return film;
        }

        public Boolean RemoveMoovie(Film film)
        {
            if (film != null)
            {
                ctx.FilmSet.Remove(film);
                ctx.SaveChanges();
                return true;
            }
            else
            {
                return false;
            }
        }

        public Boolean updateMovie(Film film)
        {
            Film result = ctx.FilmSet.SingleOrDefault(f => f.Id == film.Id);
            if (result != null)
            {
                result.name = film.name;
                result.description = film.description;
                ctx.SaveChanges();
                return true;
            }
            else
                return false;
        }
    }
}
