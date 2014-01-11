#!/bin/bash
echo "Rebuilding..."
rm -rf modules/contrib themes/
drush -y make --no-core --contrib-destination=. drupal-org.make
