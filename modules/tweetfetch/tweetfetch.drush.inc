<?php

/**
 * @file
 * Drush commands for the Tweet Fetch module.
 */

/**
 * Implements hook_drush_command().
 */
function tweetfetch_drush_command() {
  $items = array();

  $items['tweetfetch-fetch'] = array(
    'options' => array(
      'delay' => 'Seconds to wait before executing command. (Handy for staggering multiple cron jobs all running in the same minute.)',
    ),
    'description' => "Fetch tweets form Twitter REST API",
    'examples' => array(
      'drush tweetfetch-fetch' => 'Run fetch to check for new tweets, write them to file, and enable implementing modules to respond by pushing new files up to a CDN.',
      'drush tff' => '',
    ),
    'aliases' => array('tff'),
  );

  $items['tweetfetch-reset'] = array(
    'description' => "Reset counter, files, db table, since_id.",
    'examples' => array(
      'drush tweetfetch-reset' => '',
      'drush tfr' => '',
    ),
    'aliases' => array('tfr'),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function tweetfetch_drush_help($section) {
  // @todo
}

/**
 * Implements drush_hook_COMMAND().
 *
 * @see tweetfetch_drush_command()
 */
function drush_tweetfetch_fetch() {
  if ($seconds = drush_get_option('delay', 0)) {
    // Delay is used to stagger multiple drush commands running on cron in the same minute.  
    sleep($seconds);
  }

  // Run fetch. Get Twitter API response.
  $tweets = tweetfetch_fetch();

  $count = ($tweets) ? count($tweets) : 0;
  drush_print($count . " new tweets fetched.");
}

/**
 * Implements drush_hook_COMMAND().
 *
 * @see tweetfetch_drush_command()
 */
function drush_tweetfetch_reset() {
  tweetfetch_reset();
}
