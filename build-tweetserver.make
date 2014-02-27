; Tweet Server
; -------------

; Core version
; -------------
core = 7.x

; API version
; ------------
api = 2

; Drupal core
; -------------
projects[] = drupal

; Install profile
; -----------------
projects[tweetserver][type] = profile
projects[tweetserver][download][url] = http://git.drupal.org/project/tweetserver.git
projects[tweetserver][download][branch] = 7.x-1.x

; Defaults
; ---------
defaults[projects][subdir] = tweetserver

; Contrib projects
; -----------------

; This issue has been resolved in 7.x-1.x, but is not available in a tagged
; release for composer_autoload yet:
;
;   https://drupal.org/node/2052721
;
projects[composer_autoload][type] = module
projects[composer_autoload][download][revision] = 4d73302b952e46d2784fc57aede16046c2d81904

projects[] = devel
projects[] = guzzle

projects[netstorage][type] = module
projects[netstorage][download][url] = http://git.drupal.org/project/netstorage.git
projects[netstorage][download][branch] = 7.x-1.x

projects[twitterapi][type] = module
projects[twitterapi][download][url] = http://git.drupal.org/project/twitterapi.git
projects[twitterapi][download][branch] = 7.x-1.x
