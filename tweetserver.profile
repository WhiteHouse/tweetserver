<?php
/**
 * @file
 * Enables modules and site configuration for a minimal site installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function tweetserver_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = 'Tweet Server';

  $messages = array(
    t("Modules that use composer to manage dependencies need to be set up manually. Please see these modules README or INSTALL files for instructions:"),
    'Guzzle',
    'Composer Autoload',
  );
  drupal_set_message($message);
}
