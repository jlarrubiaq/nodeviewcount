<?php

/**
 * Page callback: Add node view ajax.
 *
 * @param object $node
 *   The node for counting.
 * @param object $user
 *   The user for counting.
 * @param int $timestamp
 *   When the node was viewed.
 * @param string $token
 *   Token generated to verify the URL.
 */
function nodeviewcount_count_node_view_ajax($node, $user, $timestamp, $token) {
  $is_js_way = (variable_get('nodeviewcount_way_counting', NODEVIEWCOUNT_PHP_WAY_COUNT_VIEWS) == NODEVIEWCOUNT_JS_WAY_COUNT_VIEWS);

  // Process the request only if the JS counting method is the selected.
  if ($is_js_way) {
    $token_data = array($node->nid, $user->uid, $timestamp);
    $recreated_token = _nodeviewcount_create_token($token_data);
    $is_valid_token = ($token == $recreated_token);

    // Check the request can be trusted through token validation.
    if ($is_valid_token) {
      $sessionTimeLimit = _nodeviewcount_get_session_time_limit($node->nid, TRUE);
      $sessionTimeLimitTs = ($sessionTimeLimit === FALSE) ? 0 : $sessionTimeLimit->getTimestamp();

      // Check the time limit condition is met and the view can be counted.
      if ($timestamp >= $sessionTimeLimitTs) {
        if ($node && $user) {
          $_SESSION['nodeviewcount_views_limit_js'][$node->nid] = $_SESSION['nodeviewcount_views_limit'][$node->nid];
          nodeviewcount_insert_node_view($node->nid, $user->uid);
        }
      }
    }
  }
}