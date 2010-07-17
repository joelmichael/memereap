#include "lib/routes.h"

#include "controllers/user_controller.h"

void init_routes() {
  add_route("/users/show/:id", handle_show_user);
}