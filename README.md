 while true ; do drush5 tweetfetch-fetch; drush5 queue-run netstorage_upload ; sleep 5; done;

