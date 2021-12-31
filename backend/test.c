/**
 * QuadNota-C
 * A modern and minimal notes and todo webapp written in C
 * @deltaonealpha | 26/12/2021
 * MIT License - github.com/deltaonealpha/quadnota-c/
 */

#include <stdio.h>
#include <ulfius.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>
#define PORT 8080

void do_exit(PGconn *conn, PGresult *res) {
    
    fprintf(stderr, "%s\n", PQerrorMessage(conn));    

    PQclear(res);
    PQfinish(conn);    
    
    exit(1);
}

/**
 * decode a u_map into a string
 */
char * print_map(const struct _u_map * map) {
  char * line, * to_return = NULL;
  const char **keys, * value;
  int len, i;
  if (map != NULL) {
    keys = u_map_enum_keys(map);
    for (i=0; keys[i] != NULL; i++) {
      value = u_map_get(map, keys[i]);
      len = snprintf(NULL, 0, "key is %s, value is %s", keys[i], value);
      line = o_malloc((len+1)*sizeof(char));
      snprintf(line, (len+1), "key is %s, value is %s", keys[i], value);
      if (to_return != NULL) {
        len = o_strlen(to_return) + o_strlen(line) + 1;
        to_return = o_realloc(to_return, (len+1)*sizeof(char));
        if (o_strlen(to_return) > 0) {
          strcat(to_return, "\n");
        }
      } else {
        to_return = o_malloc((o_strlen(line) + 1)*sizeof(char));
        to_return[0] = 0;
      }
      strcat(to_return, line);
      o_free(line);
    }
    return to_return;
  } else {
    return NULL;
  }
}

int callback_list_notes (const struct _u_request * request, struct _u_response * response, void * user_data) {
  PGconn *conn = PQconnectdb("dbname=defaultdb user=doadmin password=HvJSAGgg096Ixq5D host=db-postgresql-delta12542-do-user-6976795-0.b.db.ondigitalocean.com port=25060 sslmode=require");
  PGresult *res = PQexec(conn, "select json_agg(t) FROM (SELECT * from notes) t");    
  ulfius_set_string_body_response(response, 200, PQgetvalue(res, 0, 0));
  PQclear(res);
  PQfinish(conn);

  return U_CALLBACK_CONTINUE;
}

int callback_list_todo (const struct _u_request * request, struct _u_response * response, void * user_data) {
  PGconn *conn = PQconnectdb("dbname=defaultdb user=doadmin password=HvJSAGgg096Ixq5D host=db-postgresql-delta12542-do-user-6976795-0.b.db.ondigitalocean.com port=25060 sslmode=require");
  PGresult *res = PQexec(conn, "select json_agg(t) FROM (SELECT * from todo) t");    
  ulfius_set_string_body_response(response, 200, PQgetvalue(res, 0, 0));
  PQclear(res);
  PQfinish(conn);

  return U_CALLBACK_CONTINUE;
}

int callback_test (const struct _u_request * request, struct _u_response * response, void * user_data) {
  ulfius_set_string_body_response(response, 200, "QUADNOTA API - test route - response(200-valid)");

  return U_CALLBACK_CONTINUE;
}

int callback_root (const struct _u_request * request, struct _u_response * response, void * user_data) {
  ulfius_set_string_body_response(response, 200, "<!DOCTYPE html><html><head><meta charset='utf-8'><script src='https://code.jquery.com/jquery-3.6.0.js' integrity='sha256-H+K7U5CnXl1h5ywQfKtSj8PCmoN9aaq30gDh27Xc0jk=' crossorigin='anonymous'></script><meta name='viewport' content='width=device-width, initial-scale=1.0, shrink-to-fit=no'><title>QUADNOTA</title><link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'><script src='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js' integrity='sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM' crossorigin='anonymous'></script><link rel='stylesheet' href='https://fonts.googleapis.com/css?family=Nunito:200,200i,300,300i,400,400i,600,600i,700,700i,800,800i,900,900i'><link rel='stylesheet' href='https://fonts.googleapis.com/css?family=Nunito+Sans&amp;display=swap'><link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.12.0/css/all.css'><link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css'><link rel='stylesheet' href='assets/fonts/fontawesome5-overrides.min.css'><link rel='stylesheet' href='assets/css/wysiwyg.css'></head><body id='page-top' style='background: rgb(0,0,0);'><div id='wrapper'><div class='d-flex flex-column' id='content-wrapper' style='background: transparent;'><div id='content'><div class='container-fluid' style='margin-top: 55px;'><h1 style='color: #d1d1d1;font-family: 'Nunito Sans', sans-serif;margin-bottom: 0px;font-size: 25px;letter-spacing: 9px;'>QUADNOTA API</h1><h1 style='color: #adadad;font-family: 'Nunito Sans', sans-serif;margin-bottom: -5px;font-size: 14px;margin-top: 15px;'>LOCATION</h1><h1 style='color: #adadad;font-family: 'Nunito Sans', sans-serif;margin-bottom: 0px;font-size: 18px;margin-top: 5px;'><svg xmlns='http://www.w3.org/2000/svg' width='1em' height='1em' viewBox='0 0 24 24' stroke-width='2' stroke='currentColor' fill='none' stroke-linecap='round' stroke-linejoin='round' class='icon icon-tabler icon-tabler-folders' style='margin-right: 5px;margin-bottom: 5px;'><path stroke='none' d='M0 0h24v24H0z' fill='none'></path><path d='M9 4h3l2 2h5a2 2 0 0 1 2 2v7a2 2 0 0 1 -2 2h-10a2 2 0 0 1 -2 -2v-9a2 2 0 0 1 2 -2'></path><path d='M17 17v2a2 2 0 0 1 -2 2h-10a2 2 0 0 1 -2 -2v-9a2 2 0 0 1 2 -2h2'></path></svg>/</h1><div class='d-sm-flex justify-content-between align-items-center mb-4'></div><div class='row'><div class='col-lg-12 col-xl-12'><div class='card shadow mb-4' style='background: rgba(83,83,83,0.39);border-style: none;padding: 15px;padding-right: 15px;padding-left: 15px;padding-top: 15px;padding-bottom: 15px;'><h6 class='mb-0' style='font-family: 'Nunito Sans', sans-serif;font-weight: 300;font-size: 14px;color: #d1d1d1;'><strong>Methods:</strong><br><a class='btn btn-primary' role='button' style='padding-top: 5px;padding-bottom: 5px;border-radius: 5px;margin-top: 5px;margin-bottom: 15px;margin-right: 5px;background: rgb(0,0,0);border-style: none;color: #adadad;padding-left: 25px;padding-right: 25px;' href='/test'>/test</a><a class='btn btn-primary' role='button' style='padding-top: 5px;padding-bottom: 5px;border-radius: 5px;margin-top: 5px;margin-bottom: 15px;margin-right: 5px;background: rgb(0,0,0);border-style: none;color: #adadad;padding-left: 25px;padding-right: 25px;' href='/list'>/list</a><a class='btn btn-primary' role='button' style='padding-top: 5px;padding-bottom: 5px;border-radius: 5px;margin-top: 5px;margin-bottom: 15px;margin-right: 5px;background: rgb(0,0,0);border-style: none;color: #adadad;padding-left: 25px;padding-right: 25px;' href='/list/notes'>/list/notes</a><a class='btn btn-primary' role='button' style='padding-top: 5px;padding-bottom: 5px;border-radius: 5px;margin-top: 5px;margin-bottom: 15px;margin-right: 5px;background: rgb(0,0,0);border-style: none;color: #adadad;padding-left: 25px;padding-right: 25px;' href='/list/todo'>/list/todo</a><br></h6></div></div></div></div></div></div></div><style>.menulevel {background-color: rgba(83,83,83,0.39);}a {  text-decoration: none !important;}.input:focus {outline: none !important;border:3px solid #88A8E8 !important;</style><script src='https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js'></script><script src='assets/js/bs-init.js'></script><script src='assets/js/theme.js'></script><script src='assets/js/wysiwyg.js'></script></body></html>");

  return U_CALLBACK_CONTINUE;
}

int callback_root_list (const struct _u_request * request, struct _u_response * response, void * user_data) {
  ulfius_set_string_body_response(response, 200, "<!DOCTYPE html><html><head><meta charset='utf-8'><script src='https://code.jquery.com/jquery-3.6.0.js' integrity='sha256-H+K7U5CnXl1h5ywQfKtSj8PCmoN9aaq30gDh27Xc0jk=' crossorigin='anonymous'></script><meta name='viewport' content='width=device-width, initial-scale=1.0, shrink-to-fit=no'><title>QUADNOTA</title><link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'><script src='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js' integrity='sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM' crossorigin='anonymous'></script><link rel='stylesheet' href='https://fonts.googleapis.com/css?family=Nunito:200,200i,300,300i,400,400i,600,600i,700,700i,800,800i,900,900i'><link rel='stylesheet' href='https://fonts.googleapis.com/css?family=Nunito+Sans&amp;display=swap'><link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.12.0/css/all.css'><link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css'><link rel='stylesheet' href='assets/fonts/fontawesome5-overrides.min.css'><link rel='stylesheet' href='assets/css/wysiwyg.css'></head><body id='page-top' style='background: rgb(0,0,0);'><div id='wrapper'><div class='d-flex flex-column' id='content-wrapper' style='background: transparent;'><div id='content'><div class='container-fluid' style='margin-top: 55px;'><h1 style='color: #d1d1d1;font-family: 'Nunito Sans', sans-serif;margin-bottom: 0px;font-size: 25px;letter-spacing: 9px;'>QUADNOTA API</h1><h1 style='color: #adadad;font-family: 'Nunito Sans', sans-serif;margin-bottom: -5px;font-size: 14px;margin-top: 15px;'>LOCATION</h1><h1 style='color: #adadad;font-family: 'Nunito Sans', sans-serif;margin-bottom: 0px;font-size: 18px;margin-top: 5px;'><svg xmlns='http://www.w3.org/2000/svg' width='1em' height='1em' viewBox='0 0 24 24' stroke-width='2' stroke='currentColor' fill='none' stroke-linecap='round' stroke-linejoin='round' class='icon icon-tabler icon-tabler-folders' style='margin-right: 5px;margin-bottom: 5px;'><path stroke='none' d='M0 0h24v24H0z' fill='none'></path><path d='M9 4h3l2 2h5a2 2 0 0 1 2 2v7a2 2 0 0 1 -2 2h-10a2 2 0 0 1 -2 -2v-9a2 2 0 0 1 2 -2'></path><path d='M17 17v2a2 2 0 0 1 -2 2h-10a2 2 0 0 1 -2 -2v-9a2 2 0 0 1 2 -2h2'></path></svg>/list</h1><div class='d-sm-flex justify-content-between align-items-center mb-4'></div><div class='row'><div class='col-lg-12 col-xl-12'><div class='card shadow mb-4' style='background: rgba(83,83,83,0.39);border-style: none;padding: 15px;padding-right: 15px;padding-left: 15px;padding-top: 15px;padding-bottom: 15px;'><h6 class='mb-0' style='font-family: 'Nunito Sans', sans-serif;font-weight: 300;font-size: 14px;color: #d1d1d1;'><strong>Methods:</strong><br><a class='btn btn-primary' role='button' style='padding-top: 5px;padding-bottom: 5px;border-radius: 5px;margin-top: 5px;margin-bottom: 15px;margin-right: 5px;background: rgb(0,0,0);border-style: none;color: #adadad;padding-left: 25px;padding-right: 25px;' href='/list/notes'>/list/notes</a><a class='btn btn-primary' role='button' style='padding-top: 5px;padding-bottom: 5px;border-radius: 5px;margin-top: 5px;margin-bottom: 15px;margin-right: 5px;background: rgb(0,0,0);border-style: none;color: #adadad;padding-left: 25px;padding-right: 25px;' href='/list/todo'>/list/todo</a><br></h6></div></div></div></div></div></div></div><style>.menulevel {background-color: rgba(83,83,83,0.39);}a {  text-decoration: none !important;}.input:focus {outline: none !important;border:3px solid #88A8E8 !important;</style><script src='https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js'></script><script src='assets/js/bs-init.js'></script><script src='assets/js/theme.js'></script><script src='assets/js/wysiwyg.js'></script></body></html>");
  
  return U_CALLBACK_CONTINUE;
}

int callback_post_notes (const struct _u_request * request, struct _u_response * response, void * user_data) {
  printf("%s\n", ("insert into notes(heading, bodypayload) values('%s', '%s');", u_map_get(request->map_post_body, "heading"), u_map_get(request->map_post_body, "bodypayload")));
  PGconn *conn = PQconnectdb("dbname=defaultdb user=doadmin password=HvJSAGgg096Ixq5D host=db-postgresql-delta12542-do-user-6976795-0.b.db.ondigitalocean.com port=25060 sslmode=require");
  PGresult *res = PQexec(conn, "delta");    
  PQclear(res);
  PQfinish(conn);
  ulfius_set_string_body_response(response, 200, ("200"));
  return U_CALLBACK_CONTINUE;
}

/**
 * main function
 */
int main(void) {
  struct _u_instance instance;

  // Initialize instance with the port number
  if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
    fprintf(stderr, "Error ulfius_init_instance, abort\n");
    return(1);
  }

  // Endpoint list declaration
  ulfius_add_endpoint_by_val(&instance, "GET", "/list/notes", NULL, 0, &callback_list_notes, NULL);
  ulfius_add_endpoint_by_val(&instance, "GET", "/list/todo", NULL, 0, &callback_list_todo, NULL);
  ulfius_add_endpoint_by_val(&instance, "GET", "/test", NULL, 0, &callback_test, NULL);
  ulfius_add_endpoint_by_val(&instance, "GET", "/", NULL, 0, &callback_root, NULL);
  ulfius_add_endpoint_by_val(&instance, "GET", "/list", NULL, 0, &callback_root_list, NULL);
  ulfius_add_endpoint_by_val(&instance, "POST", "/post/notes", NULL, 0, &callback_post_notes, NULL);

  // Start the framework
  if (ulfius_start_framework(&instance) == U_OK) {
    printf("Start framework on port %d\n", instance.port);

    // Wait for the user to press <enter> on the console to quit the application
    getchar();
  } else {
    fprintf(stderr, "Error starting framework\n");
  }
  printf("End framework\n");

  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);

  return 0;
}
