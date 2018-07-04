using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MovieNet.Data
{
    class Login
    {
        private DataModelContainer ctx = null;

        public Login(DataModelContainer context)
        {
            ctx = context;
        }

        public User Authenticate(String login, String password)
        {
            User usr = null;

            Console.WriteLine(login);
            var query = ctx.UserSet.Where(u => u.login.Equals(login) && u.password.Equals(password)).ToList();
            if (query.Count() > 0)
                usr = query.First();
            return usr;
        }

        public User Register(String login, String password)
        {
            User usr = new User();

            usr.login = login;
            usr.password = password;

            var query = ctx.UserSet.Add(usr);
            ctx.SaveChanges();
            
            return query;
        }
    }
}
