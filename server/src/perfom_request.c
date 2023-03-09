#include "server.h"
// // char *str = "{ \"type\": \"GET\", \
//     //     \"property\": { \"login\": \"nemmmmmmmdadmm\", \
//     //     \"password\": \"1223\", \
//     //     \"nick_name\": \"1223\", \
//     //     \"first_name\": \"1223\", \
//     //     \"last_name\": \"1223\" \
//     //     }" \
//     //     "}";

// switch: req.url == users {
//     perform_req(req, res, NULL, getAll_users(db, req.prop))
// }
// int perform_req(t_requests* req, char* res, t_vallidator validator, t_cotroller controller, sqlite3* db) {
//     if(validator != NULL) {
//         req->status = validator(req->property);
//         if(req->status != 200) {
//             return 1;
//         }
//     }

//     http.get(url, req, res, VALID, Model.user);
//     axios.post(url, req, res, VALID, Model.user);
//     axios.delete(url, req, res, VALID, Model.user);
      
//     res = controller(db, req->property);

//     return 0;
// }
