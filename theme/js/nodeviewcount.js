jQuery(document).ready(function($) {
  var nodeviewcount_insert_node_view = function(nid, uid) {
    var nodeviewcount_path = Drupal.settings.nodeviewcount.nodeviewcount_path;
    var nodeviewcount_timestamp = Drupal.settings.nodeviewcount.nodeviewcount_timestamp;
    var nodeviewcount_token = Drupal.settings.nodeviewcount.nodeviewcount_token;
    $.ajax({
      type: 'POST',
      url: Drupal.settings.basePath + nodeviewcount_path + '/' + nid + '/' + uid + '/' + nodeviewcount_timestamp + '/' + nodeviewcount_token,
      dataType: 'json'
    });
  }
  var nodeviewcount_nid = Drupal.settings.nodeviewcount.nodeviewcount_nid;
  var nodeviewcount_uid = Drupal.settings.nodeviewcount.nodeviewcount_uid;
  nodeviewcount_insert_node_view(nodeviewcount_nid, nodeviewcount_uid);
});