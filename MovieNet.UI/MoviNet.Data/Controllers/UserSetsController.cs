using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Data.Entity.Infrastructure;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using System.Web.Http.ModelBinding;
using System.Web.Http.OData;
using System.Web.Http.OData.Routing;
using MoviNet.Data.Models;

namespace MoviNet.Data.Controllers
{
    /*
    The WebApiConfig class may require additional changes to add a route for this controller. Merge these statements into the Register method of the WebApiConfig class as applicable. Note that OData URLs are case sensitive.

    using System.Web.Http.OData.Builder;
    using System.Web.Http.OData.Extensions;
    using MoviNet.Data.Models;
    ODataConventionModelBuilder builder = new ODataConventionModelBuilder();
    builder.EntitySet<UserSet>("UserSets");
    config.Routes.MapODataServiceRoute("odata", "odata", builder.GetEdmModel());
    */
    public class UserSetsController : ODataController
    {
        private Database1Entities2 db = new Database1Entities2();

        // GET: odata/UserSets
        [EnableQuery]
        public IQueryable<UserSet> GetUserSets()
        {
            return db.UserSets;
        }

        // GET: odata/UserSets(5)
        [EnableQuery]
        public SingleResult<UserSet> GetUserSet([FromODataUri] int key)
        {
            return SingleResult.Create(db.UserSets.Where(userSet => userSet.Id == key));
        }

        // PUT: odata/UserSets(5)
        public IHttpActionResult Put([FromODataUri] int key, Delta<UserSet> patch)
        {
            Validate(patch.GetEntity());

            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            UserSet userSet = db.UserSets.Find(key);
            if (userSet == null)
            {
                return NotFound();
            }

            patch.Put(userSet);

            try
            {
                db.SaveChanges();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!UserSetExists(key))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return Updated(userSet);
        }

        // POST: odata/UserSets
        public IHttpActionResult Post(UserSet userSet)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            db.UserSets.Add(userSet);
            db.SaveChanges();

            return Created(userSet);
        }

        // PATCH: odata/UserSets(5)
        [AcceptVerbs("PATCH", "MERGE")]
        public IHttpActionResult Patch([FromODataUri] int key, Delta<UserSet> patch)
        {
            Validate(patch.GetEntity());

            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            UserSet userSet = db.UserSets.Find(key);
            if (userSet == null)
            {
                return NotFound();
            }

            patch.Patch(userSet);

            try
            {
                db.SaveChanges();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!UserSetExists(key))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return Updated(userSet);
        }

        // DELETE: odata/UserSets(5)
        public IHttpActionResult Delete([FromODataUri] int key)
        {
            UserSet userSet = db.UserSets.Find(key);
            if (userSet == null)
            {
                return NotFound();
            }

            db.UserSets.Remove(userSet);
            db.SaveChanges();

            return StatusCode(HttpStatusCode.NoContent);
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                db.Dispose();
            }
            base.Dispose(disposing);
        }

        private bool UserSetExists(int key)
        {
            return db.UserSets.Count(e => e.Id == key) > 0;
        }
    }
}
