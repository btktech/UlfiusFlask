#include <ulfius.h>
#include <jansson.h>

#define LOGIN_OK 0

int error = -1;
char *username = "admin";
char *password = "admin";


int login_init_header(struct _u_map *header){
    if(u_map_init(header) != U_OK){
        return -1;
    }
    if(u_map_put(header, "Content-Type", "application/json") != U_OK){
        printf("ERROR: Content-Type error.\n");
        return -1;
    }
    if(u_map_put(header, "Accept", "application/json") != U_OK){
        printf("ERROR: Accept error.\n");
        return -1;
    }

    return 0;
}

int check_resposne(const json_t *j_resp, const char *username){
    json_t *j_code = json_object_get(j_resp, "code");
    if(j_resp == NULL){
        printf("JSON RESPONSE NULL.\n");
        return -1;
    }

    if(j_code == NULL){
        printf("JSON CODE NULL.\n");
        return -1;
    }

    if(json_integer_value(j_code) == 200){
        printf("LOGIN SUCCESS.\n");
        return 0;
    }
}

int new_user_request(char *username, char*password)
{
    json_t *json_login = json_object();
    struct _u_map header;
    struct _u_response response;
    char u[256];
    char p[256];
    char url[256] = "http://127.0.0.1:5000/new_users";

    if(login_init_header(&header) != LOGIN_OK){
        printf("ERROR: New User - http init header error.\n");
        return -1;
    }

    if(json_object_set_new(json_login,"username", json_string(username)) != 0){
        printf("ERROR: New User - JSON set username value error.\n");
        return -1;
    }
    if(json_object_set_new(json_login,"password", json_string(password)) != 0){
        printf("ERROR: New User - JSON set password value error.\n");
        return -1;
    }

    // request //
    struct _u_request request = {"POST", url, 1, NULL, NULL, NULL, NULL, &header, NULL, NULL, json_login, NULL, 0, NULL, 0};

    // request.auth_basic_user = strdup(username);
    // request.auth_basic_password = strdup(password);

    printf("username = %s\n", username);
    printf("password = %s\n", password);

    if(ulfius_init_response(&response) != U_OK){
        printf("ERROR: New User - init response error.\n");
    }

    if(ulfius_send_http_request(&request, &response) != U_OK){
        printf("ERROR: New User - Failed to connect Server.\n");
        u_map_clean(&header);
        return -1;
    }

    check_resposne(response.json_body, username);

}
//..//


int user_login_request(char *username, char*password)
{
    json_t *json_login = json_object();
    struct _u_map header;
    struct _u_response response;
    char u[256];
    char p[256];
    char url[256] = "http://127.0.0.1:5000/login";

    if(login_init_header(&header) != LOGIN_OK){
        printf("ERROR: Login - http init header error.\n");
        return -1;
    }

    if(json_object_set_new(json_login,"username", json_string(username)) != 0){
        printf("ERROR: Login - JSON set username value error.\n");
        return -1;
    }
    if(json_object_set_new(json_login,"password", json_string(password)) != 0){
        printf("ERROR: Login - JSON set password value error.\n");
        return -1;
    }

    // request //
    struct _u_request request = {"POST", url, 1, NULL, NULL, NULL, NULL, &header, NULL, NULL, json_login, NULL, 0, NULL, 0};

    // request.auth_basic_user = strdup(username);
    // request.auth_basic_password = strdup(password);

    printf("username = %s\n", username);
    printf("password = %s\n", password);

    if(ulfius_init_response(&response) != U_OK){
        printf("ERROR: Login - init response error.\n");
    }

    if(ulfius_send_http_request(&request, &response) != U_OK){
        printf("ERROR: Login - Failed to connect Server.\n");
        u_map_clean(&header);
        return -1;
    }

    check_resposne(response.json_body, username);

}

int user_logout_request(char *username)
{
    json_t *json_logout = json_object();
    struct _u_map header;
    struct _u_response response;
    char u[256];
    char p[256];
    char url[256] = "http://127.0.0.1:5000/logout";

    if(login_init_header(&header) != LOGIN_OK){
        printf("ERROR: Logout - http init header error.\n");
        return -1;
    }

    if(json_object_set_new(json_logout,"username", json_string(username)) != 0){
        printf("ERROR: Logout - JSON set username value error.\n");
        return -1;
    }
    // request //
    struct _u_request request = {"POST", url, 1, NULL, NULL, NULL, NULL, &header, NULL, NULL, json_logout, NULL, 0, NULL, 0};

    request.auth_basic_user = strdup(username);

    printf("Logout - username = %s\n", username);

    if(ulfius_init_response(&response) != U_OK){
        printf("ERROR: Logout - init response error.\n");
    }

    if(ulfius_send_http_request(&request, &response) != U_OK){
        printf("ERROR: Logout - Failed to connect Server.\n");
        u_map_clean(&header);
        return -1;
    }

    check_resposne(response.json_body, username);

}

int main(int argc, char **argv)
{
    printf("Call from main function\n");
    printf("argc = %d\n", argc);
    printf("argv[0] = %s\n", argv[0]);
    if(argc > 1) printf("argv[1] = %s\n", argv[1]);

    if(argc == 1){
        printf("Only Login\n");
        user_login_request(username, password);
    }
    else if(argc == 2 && strcmp(argv[1], "new_users") == 0){
        printf("NEW USER\n");
        new_user_request(username, password);
    }
    else if(argc == 2 && strcmp(argv[1], "login") == 0){
        printf("LOGIN\n");
        user_login_request(username, password);
    }
    else if(argc == 2 && strcmp(argv[1], "logout") == 0){
        printf("LOGOUT\n");
        user_logout_request(username);
    }
    
    printf("DONE.\n");
}