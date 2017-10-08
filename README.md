### Intro

This is enhanced version of the Drupal 7 module nodeviewcount, solving some
security issues.

### Problems

The original module implementation allows any person knowing a user and node
id to write in DB a new view record through the menu element:
```
nodeviewcount/%nodeviewcount_node/%nodeviewcount_user
```
used to count views by AJAX.

This leads to two potential problems:
- No real views might be registered.
- An open gate to attacks, as DB writes are quite expensive operations,
it could easily make a site unavailable.

### Solution

The solution provides **token validation** to verify the requested URL.
Now, the menu element path contains the timestamp when the node was viewed and
the token generated using nid/uid/timestamp and a secret key.
This way, we can ensure the URL was generated and requested by a trusted user
and the time limit condition to count a new view is respected.

Other changes to take into account:

- Created the functions  
```_nodeviewcount_create_token``` and
```_nodeviewcount_get_session_time_limit``` as the same logic is used in both,
the menu page callback (nodeviewcount.pages.inc) and the main module file.

- Added a new session variable ```'nodeviewcount_views_limit_js'```
as it is needed to check if the time limit condition is met at the menu page
callback side ```nodeviewcount_count_node_view_ajax```.
It stores the same info as ```'nodeviewcount_views_limit'``` but it is updated
when the token is actually validated.

- The secret key is user configurable from the admin menu and I've added an
update function to initialize its value.

### How to use it

The code includes the improved solution for the latest version of the module
dev branch (7.x-3.x) and corresponding patch.

### Original source

[Node view count module](https://www.drupal.org/project/nodeviewcount)