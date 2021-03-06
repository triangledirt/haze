#include "cf/x/core/standard.h"
#include "cf/x/net/post/stats.h"

void cf_x_net_post_stats_init(cf_x_net_post_stats_t *post_stats)
{
  assert(post_stats);

  post_stats->messages_sent = 0;
  post_stats->messages_received = 0;
  post_stats->messages_in_inbox = 0;
  post_stats->messages_in_outbox = 0;
  post_stats->most_messages_ever_in_inbox = 0;
  post_stats->most_messages_ever_in_outbox = 0;
  post_stats->send_message_failures = 0;
  post_stats->receive_message_failures = 0;
  post_stats->incoming_message_size_pseudo_average = 0;
  post_stats->messages_not_sent_due_to_socket_send_failures = 0;
}
