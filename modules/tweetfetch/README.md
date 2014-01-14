Tweet Fetch
===========

This module fetches tweets from Twitter via GET requests to the REST API
documented here: https://dev.twitter.com/docs/api/1.1/

Usage
=====

  Configure and test your GET request here:

    admin/config/tweetfetch


  Set up a cron job or a script to poll Twitter for new tweets like this:

    drush tweet-fetch


  New tweets will be stored like this:

    sites/<default>/files/tweets/0.json
    sites/<default>/files/tweets/1.json
    sites/<default>/files/tweets/2.json
                                  .    
                                  .    
                                  .    
    sites/<default>/files/tweets/N.json
