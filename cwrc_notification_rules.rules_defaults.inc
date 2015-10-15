<?php
/**
 * @file
 * cwrc_notification_rules.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function cwrc_notification_rules_default_rules_configuration() {
  $items = array();
  $items['rules_send_application_approved_email'] = entity_import('rules_config', '{ "rules_send_application_approved_email" : {
      "LABEL" : "Send application approved email",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "notification", "og" ],
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_approved" : [] },
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "og-membership" ], "type" : "og_membership" } },
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } },
        { "node_is_of_type" : {
            "node" : [ "og-membership:group" ],
            "type" : { "value" : { "project" : "project" } }
          }
        }
      ],
      "DO" : [
        { "entity_fetch" : {
            "USING" : { "type" : "node", "id" : [ "og-membership:group:nid" ] },
            "PROVIDE" : { "entity_fetched" : { "node_group_loaded" : "Loaded group node" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your application to join [node-group-loaded:title] has been rejected",
            "message" : "Dear [account:name],\\r\\n\\r\\nYour application to join the group [node-group-loaded:title] has been approved.\\r\\n\\r\\nYou can view the group at: [node-group-loaded:url]\\r\\n\\r\\nthanks,\\r\\n-- The staff at the Canadian Writing Research Centre collaboratory",
            "language" : [ "account:language" ]
          }
        }
      ]
    }
  }');
  $items['rules_send_application_rejected_email'] = entity_import('rules_config', '{ "rules_send_application_rejected_email" : {
      "LABEL" : "Send application rejected email",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "notification", "og" ],
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_blocked" : [] },
      "IF" : [
        { "entity_is_of_type" : { "entity" : [ "og-membership" ], "type" : "og_membership" } },
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } },
        { "node_is_of_type" : {
            "node" : [ "og-membership:group" ],
            "type" : { "value" : { "project" : "project" } }
          }
        }
      ],
      "DO" : [
        { "entity_fetch" : {
            "USING" : { "type" : "node", "id" : [ "og-membership:group:nid" ] },
            "PROVIDE" : { "entity_fetched" : { "node_group_loaded" : "Loaded group node" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your application to group [node-group-loaded:title] has been rejected",
            "message" : "Dear [account:name],\\r\\n\\r\\nYour application to join the group [node-group-loaded:title] has been rejected.\\r\\n\\r\\nIf you wish to reapply, you can do so from: [node-group-loaded:url]\\r\\n\\r\\nthanks,\\r\\n-- The staff at the Canadian Writing Research Centre collaboratory",
            "language" : [ "account:language" ]
          }
        }
      ]
    }
  }');
  return $items;
}
