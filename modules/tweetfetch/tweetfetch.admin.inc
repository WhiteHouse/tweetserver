<?php
/**
 * Callback for admin/config/tweetfetch.
 *
 * @see system_settings_form
 */
function tweetfetch_admin_config() {
  $form = array();

  $form['twitterfetch_request'] = array(
    '#type' => 'textarea',
    '#title' => t('Twitter REST API GET request'),
    '#default_value' => variable_get('twitterfetch_request', 'statuses/user_timeline.json?screen_name=whitehouse&count=1&include_rts=1'),
    '#description' => t('Enter any supported GET request documented on !docs', array('!docs' => l('dev.twitter.com/docs/api/1.1', 'https://dev.twitter.com/docs/api/1.1'))),
    '#rows' => 2,
  );

  $form['twitterfetch_tryit'] = array(
    '#type' => 'submit',
    '#value' => t('Try it!'),
    '#submit' => array('tweetfetch_config_tryit'),
  );

  return system_settings_form($form);
}

/**
 * Callback for "try it" button.
 */
function tweetfetch_config_tryit() {
  $request = variable_get('twitterfetch_request', '');

  $twitter_api = new TwitterApi();
  $response = $twitter_api->get($request);

  if (module_exists('devel')) {
    dpm($request, 'request');
    dpm($response, 'response');
  }
  else {
    $response = drupal_json_encode($response);
    drupal_set_message("$request");  
    drupal_set_message("<pre>$response</pre>");  
  }
}
