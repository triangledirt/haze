#include "cf/x/core/message.h"
#include "cf/x/core/tools.h"
#include "cf/x/net/client/system.h"
#include "cf/x/net/pingpong/engine.h"
#include "cf/x/net/pingpong/message.h"
#include "cf/x/net/pingpong/ping.h"

#define PING_CLIENT_SLEEP_MICROSECONDS CF_X_CORE_STANDARD_SLEEP_MICROSECONDS
#define PING_CLIENT_SEND_MESSAGE_COUNT 8

struct ping_client_context_t {
  cf_x_core_bool_t pong_received;
  unsigned short pongs_received;
};
typedef struct ping_client_context_t ping_client_context_t;

static void handle_pong(void *custom_client_context,
    cf_x_core_message_t *message);
static void print_uinferno_exit();

void handle_pong(void *custom_client_context, cf_x_core_message_t *message)
{
  assert(custom_client_context);
  assert(message);
  ping_client_context_t *client_context;
  char *pong_string;

  client_context = custom_client_context;

  client_context->pong_received = cf_x_core_bool_true;
  client_context->pongs_received++;
  pong_string = cf_x_core_message_take_string(message);
  printf("[ping] server sent back \"%s\"\n", pong_string);

  free(pong_string);
}

void print_uinferno_exit()
{
  printf("\n    uinferno: ping_client serverIp serverPort pingMessage\n\n");
  exit(1);
}

int main(int argc, char *argv[])
{
  cf_x_net_client_system_t *client;
  cf_x_core_message_t *ping_message;
  ping_client_context_t ping_client_context;
  cf_x_pingpong_ping_t *ping;
  cf_x_core_log_t *log;

  unsigned short server_port;
  char *server_ip;
  char *ping_string;

  unsigned short message_count;

  signal(SIGPIPE, SIG_IGN);

  if (argc < 4) {
    print_uinferno_exit();
  }
  server_ip = argv[1];
  server_port = atoi(argv[2]);
  ping_string = argv[3];

  ping_client_context.pong_received = cf_x_core_bool_false;
  ping_client_context.pongs_received = 0;

  log = cf_x_core_log_create(stdout);
  if (!log) {
    cf_x_core_trace_exit("x_audit_log_create");
  }

  client = cf_x_net_client_system_create(server_ip, server_port, server_port,
      CF_X_NET_ENGINE_NO_GET_NAME_FUNCTION, &ping_client_context, log);
  if (!client) {
    cf_x_core_trace_exit("x_net_client_create");
  }

  if (!cf_x_net_client_system_register_engine(client, CF_X_NET_ENGINE_PING,
          cf_x_PINGPONG_MESSAGE_TYPE_COUNT)) {
    cf_x_core_trace_exit("x_net_client_register_engine");
  }

  cf_x_net_client_system_register_message_handler(client, CF_X_NET_ENGINE_PING,
      cf_x_PINGPONG_MESSAGE_PONG, handle_pong);

  for (message_count = 0; message_count < PING_CLIENT_SEND_MESSAGE_COUNT;
       message_count++) {

    ping = cf_x_pingpong_ping_create(ping_string);
    if (ping) {
      ping_message = cf_x_pingpong_message_create
        (CF_X_CORE_IMESSAGE_NO_CLIENT_SOCKET, cf_x_PINGPONG_MESSAGE_PING);
      if (ping_message) {
        if (cf_x_pingpong_ping_add_to_message(ping, ping_message)) {
          if (!cf_x_net_client_system_send_message(client, ping_message)) {
            cf_x_core_trace_exit("x_net_client_send_message() failed");
          }
        } else {
          cf_x_core_trace("x_pingpong_ping_add_to_message");
          cf_x_core_message_destroy(ping_message);
        }
      } else {
        cf_x_core_trace("x_pingpong_message_create");
      }
      cf_x_pingpong_ping_destroy(ping);
    } else {
      cf_x_core_trace_exit("x_pingpong_ping_create");
    }
  }

  do {
    cf_x_net_client_system_process_messages(client);
    usleep(PING_CLIENT_SLEEP_MICROSECONDS);
  } while (ping_client_context.pongs_received
      < PING_CLIENT_SEND_MESSAGE_COUNT);

  cf_x_net_client_system_destroy(client);
  cf_x_core_log_destroy(log);

  return 0;
}
