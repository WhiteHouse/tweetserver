<?php
/**
 * @file
 * Admin page for tweetfetch module.
 */

/**
 * Callback for admin/config/tweetfetch.
 *
 * @see system_settings_form
 */
function tweetfetch_admin_config() {
  // Check to see if user has set up credentials. If not, warn them nothing will
  // work.
  if (!$credentials = variable_get('twitterapi_credentials', FALSE)) {
    $text = t("Looks like you're missing Twitter REST API credentials. See twitterapi/README and get your credentials set up before you proceed. Otherwise nothing will work.");
    drupal_set_message($text, 'error');
  }

  $form = array();

  $form['tweetfetch_description'] = array(
    '#type' => 'item',
    '#title' => 'About',
    '#description' => t("Enter a Twitter API request below then click Fetch (or set it up to run continuously via `drush tweetfetch`). The first time your request runs, Tweet Fetch keeps track of the time and id of the latest tweet in the timeline. After that, Tweet Fetch continues checking for newer tweets, storing them, and writing them to static JSON files like this: sites/default/files/tweets/0.json, tweets/1.json, tweets/2.json, ... tweets/3.json, etc.). When a new tweet is successfully fetched, hook_tweetfetch fires and gives other modules an opportunity to respond (for example, to queue a job to push the latest file up to a CDN). To start counting over from 0, and to zero out existing JSON files, click Reset. (NOTE: If files have already been pushed up to a CDN, this Reset will NOT remove files from your CDN.) To test out your API request, just click Try It."),
  );

  $form['tweetfetch_request'] = array(
    '#type' => 'textarea',
    '#title' => t('Twitter Timeline API request'),
    '#default_value' => variable_get('tweetfetch_request', ''),
    '#description' => t('Enter a GET request for any timeline documented on !docs', array('!docs' => url('https://dev.twitter.com/docs/api/1.1'))),
    '#rows' => 2,
  );

  $form['tweetfetch_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Debug'),
    '#default_value' => variable_get('tweetfetch_debug', FALSE),
    '#description' => t('Use dummy data for testing.'),
  );

  $form['tweetfetch_fetch'] = array(
    '#type' => 'submit',
    '#value' => t('Fetch'),
    '#submit' => array('tweetfetch_fetch_tryit'),
  );

  $form['tweetfetch_reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#submit' => array('tweetfetch_reset_tryit'),
  );

  $form['tweetfetch_tryit'] = array(
    '#type' => 'submit',
    '#value' => t('Try it!'),
    '#submit' => array('tweetfetch_config_tryit'),
  );

  return system_settings_form($form);
}

/**
 * Validation.
 */
function tweetfetch_admin_config_validate($form, &$form_state) {
  $request = $form_state['values']['tweetfetch_request'];

  if (strpos($request, 'since_id')) {
    form_set_error('since_id', 'since_id: The since_id will be appended to your request automatically, using the last since_id recorded in the database. Do not hard code it here.');
  }

  // @todo Check for count. Advise not to set count < 5.
}

/**
 * Callback for "try it" button.
 */
function tweetfetch_config_tryit($form, &$form_state) {
  _tweetfetch_update_admin_settings($form_state['values']);

  $response = _tweetfetch_fetch();
  $debug = variable_get('tweetfetch_debug', FALSE);
  $request = ($debug) ? 'Dummy data request: statuses/json-examples/user_timeline.screen_name=whitehouse.count=10.json' : tweetfetch_get_request();

  if (module_exists('devel')) {
    dpm($request, 'request');
    dpm($response, 'response');
  }
  else {
    $response = drupal_json_encode($response);
    drupal_set_message("Request: " . $request);
    drupal_set_message("<pre>$response</pre>");
  }
}

/**
 * Wrapper around tweetfetch_fetch().
 */
function tweetfetch_fetch_tryit($form, &$form_state) {
  _tweetfetch_update_admin_settings($form_state['values']);

  // @todo For some reason dsm() and drupal_set_message are only appearing on
  // second page load. Maybe related? https://drupal.org/node/54024
  // Data in db looks like it's coming out alright, so maybe this is an
  // just a cosmetic bug.
  if ($response = tweetfetch_fetch()) {
    if (module_exists('devel')) {
      dpm($response, 'response');
    }
    else {
      drupal_set_message("<pre>$response</pre>");
    }
  }

}

/**
 * Wrapper around tweetfetch_reset().
 */
function tweetfetch_reset_tryit() {
  tweetfetch_reset();
}

/**
 * Update admin settings.
 *
 * @param array $values
 *   Values from $form_state['values']
 */
function _tweetfetch_update_admin_settings($values) {
  $settings = array(
    'tweetfetch_request',
    'tweetfetch_debug',
  );
  foreach ($settings as $setting) {
    $value = $values[$setting];
    variable_set($setting, $value);
  }
}
