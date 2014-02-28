Tweet Server
============

About
-----

  Tweet Server is a light weight, Drupal-based application that grabs tweets from
  Twitter and stores them as static JSON files in Drupal's files directory (or
  optionally pushes them up to a CDN). This enables you to curate your own
  Twitter timeline and access the full content of a tweet as machine readable
  data, to incorporate it to your website with the most possible flexibility.

  Tweet Server was originally developed by the White House for the State of the
  Union Address on January 28, 2014. It was used to enable whitehouse.gov to do two
  things:
    
    1. Consume a custom Twitter timeline that would display live tweets timed with the
       President's speech while the live event was streaming at whitehouse.gov/state-of-the-union-2014

    2. Give client-side JavaScript full access to the contents of @whitehouse
       tweets and twitpics, to be parsed and rendered either below the video or as
       a slideshow

  Version 1 is a simple, feature-complete, proof-of-concept. It only works with
  a single Twitter timeline.

  Version 2 (not developed yet) might include support for multiple different
  Twitter timelines and fancier UI controls for managing tweets for live events.
  Contributions welcome!


Dependencies
------------

  - composer


Usage
-----

  Configure Tweet Server to pull in tweets from Twitter's REST API. Then store
  tweets in static JSON files where consumers (e.g. client-side JavaScript) can
  access them.

  Tweets are stored in Tweet Server's public files directory like this (for
  multisite installations "default" would be replaced with the name of your site
  directory):

    sites/default/files/tweets/0.json
    sites/default/files/tweets/1.json
    sites/default/files/tweets/2.json
                                  .        
                                  .        
                                  .        
    sites/default/files/tweets/N.json

  Optionally push these files up to Akamai Netstorage using the included
  Netstorage module or any other CDN you choose to integrate with. (Integration is
  easy. See how Netstorage module implements hook_tweetfetch and
  hook_cron_queue_info).


Installation and setup
----------------------

  1. Install the Tweet Server installation profile.

  2. Finish installing guzzle and composer_autoload modules like this (see
     readmes included with projects for more info):

  ```bash
    # Note: Contrib projects included in the tweetserver distro live in
    # sites/all/modules/tweetserver 

    cd sites/all/modules/tweetserver/guzzle
    composer install

    cd sites/all/modules/tweetserver/guzzle
    composer install
  ```

  3. Follow instructions in Twitter API module to get Twitter credentials and
     store them in settings.php. This is a contrib module, included in the
     distro here: 
     
        sites/all/modules/tweetserver/twitterapi/README.md

  4. Configure and test your GET request to Twitter's API to pull in tweets
     here:
    
        admin/config/tweetfetch

     More info included with Tweet Fetch module:

        profiles/tweetserver/modules/tweetfetch/README.md
  
  5. (Optional) Configure your site to push JSON tweet files up to Akamai
     Netstorage. Include configuration in settings.php as described here:

        sites/all/modules/tweetserver/netstorage/README.md

  6. By default, Tweet Fetch only fetches tweets that include pictures,
    "twitpics". To fetch ALL tweets, disable the twitpic_only module. To
    implement your own custom filter, implement hook_tweetfetch_tweet_alter in
    your own module. See a simple example of how twitpic_only does this here:

        profiles/tweetserver/modules/tweetfetch/twitpic_only.module 

  7. Set up Tweet Server to slurp in tweets and make them available to consumers
     on a schedule that suits you.

       Run tweet fetch manually through the GUI here: 
        admin/config/tweetfetch

       Run tweet fetch manually or on cron via Drush like this:
        drush tweetfetch-fetch

       For a live event, where you want to pull in tweets in near-realtime and
       make them available as quickly as possible, one simple approach is to run
       a simple bash loop. 

  ```bash
    # ssh into your server and start a screen session (recommended)
    screen

    # Now start a loop. Kill it with ctrl+c.
    #
    # NOTE: Be careful not to go over Twitter's rate limits. You can easily
    # double check the rate limit with a simple utility provided by Twitter
    # API module. For whatever REST resource you're interested in make a
    # request like this (if you're not interested in statuses, replace that
    # with any supported REST API resource):
    #
    #   drush twitterapi-get 'https://api.twitter.com/1.1/application/rate_limit_status.json?resources=statuses' 
    #
    # NOTE ALSO: If you need realtime data, you may want to look into using
    # Twitter's Streaming API here: https://dev.twitter.com/docs/api/streaming.
    # Tweet Server version 1 only uses the Twitter's REST API.
    #
    while true ; do drush5 tweetfetch-fetch; sleep 5; done;

    # To have your loop sync tweet JSON files to Netstorage, do this:
    while true ; do drush5 tweetfetch-fetch; drush5 queue-run netstorage_upload ; sleep 5; done;
  ```
