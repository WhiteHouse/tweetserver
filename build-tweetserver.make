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
projects[drupal][version] = 7.25

; Install profile
; -----------------
projects[tweetserver][type] = profile
projects[tweetserver][download][branch] = 7.x-1.x
projects[tweetserver][download][tag] = 7.x-1.0-rc5
projects[tweetserver][subdir] = ''

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
projects[composer_autoload][download][revision] = 4d73302

projects[devel][version] = 1.3

projects[guzzle][download][revision] = 0dbe667

projects[netstorage][type] = module
projects[netstorage][download][branch] = 7.x-1.x
projects[netstorage][download][tag] = 7.x-1.0-rc1

projects[twitterapi][type] = module
projects[twitterapi][download][branch] = 7.x-1.x
projects[twitterapi][download][tag] = 7.x-1.0-rc1
