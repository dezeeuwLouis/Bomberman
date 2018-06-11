using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DOT_NET
{
    class Program
    {
        static void Main(string[] args)
        {
            DataModelContainer ctx = new DataModelContainer();
            Produit produit = new Produit();
            User user = new User();

            user.login = "michel";
            user.password = "mich";

            ctx.UserSet.Add(user);

            var query = ctx.UserSet.Where(u => u.login.Contains("i")).ToList();

            ctx.SaveChanges();
        }
    }
}
