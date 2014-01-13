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
projects[tweetserver][download][type] = git
projects[tweetserver][download][url] = git://github.com/bryanhirsch/tweetserver.git
projects[tweetserver][download][branch] = 7.x-1.x

; Defaults
; ---------
defaults[projects][subdir] = tweetserver

; Contrib projects
; -----------------
projects[] = composer_autoload
projects[] = devel
projects[] = guzzle

projects[netstorage][type] = module
projects[netstorage][download][type] = git
projects[netstorage][download][url] = git://github.com/bryanhirsch/netstorage.git
projects[netstorage][download][branch] = 7.x-1.x

projects[twitterapi][type] = module
projects[twitterapi][download][type] = git
projects[twitterapi][download][url] = git://github.com/bryanhirsch/twitterapi.git
projects[twitterapi][download][branch] = 7.x-1.x
