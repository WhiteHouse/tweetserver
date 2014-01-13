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

projects[twitter_api][type] = module
projects[twitter_api][download][type] = git
projects[twitter_api][download][url] = git://github.com/bryanhirsch/twitter_api.git
projects[twitter_api][download][branch] = 7.x-1.x
