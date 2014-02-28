Tweet Fetch
===========

This module fetches tweets from Twitter via GET requests to the REST API
documented here: https://dev.twitter.com/docs/api/1.1/

Usage
-----

  Configure and test your GET request here:

    admin/config/tweetfetch


  Set up a cron job or a script to poll Twitter for new tweets like this:

    drush tweetfetch-fetch
    drush tff


  New tweets will be stored like this:

    sites/<default>/files/tweets/0.json
    sites/<default>/files/tweets/1.json
    sites/<default>/files/tweets/2.json
                                  .    
                                  .    
                                  .    
    sites/<default>/files/tweets/N.json


Hooks
-----

  hook_tweetfetch

    Modules can implement hook_tweetfetch($filepath) to capture the path to new files
    and react (e.g. queue for pushing up to CDN).


  hook_tweetfetch_tweet_alter(&$tweet, &$op)

    Alter contents of $tweet before it's stored as JSON and alter $op to
    determine how tweet will be processed (saved or skipped).


  hook_tweetfetch_reset

    Hook into reset event to clear caches locally or at CDN.
