#!/bin/sh
# Copyright © 2018 Joshua Nelson under GNU GPL v3.0
#
# To paraphrase Richard Stallman:
# > Use it, copy it, modify it, and distribute modified versions
# > but don't add more restrictions.
# See https://www.gnu.org/licenses/gpl-3.0.en.html for details
#
# Inspired by [linklint](http://www.linklint.org/)
#
# To see only errors, run `check_links.sh | grep -v Success`
#
# TODO:
#	- Fix html regex, it breaks sometimes (??)
#	- Make it faster. It's very, very slow.
#
######### Start ####################
# echo commands as they are executed
set -v
# throw an error if no links found
set -u

# install this with `pip install markdown_py`
markdown_py more_links.md > more_links.html

# still picks up some bad html, working on it
LINKS=$(grep -o '"https\?://.*"' more_links.html | tr -d '"')

# delete checks.txt if present
echo > checks.txt

for link in $LINKS; do
	printf "Checking $link... " | tee checks.txt
	if curl -s -S $link > /dev/null | tee checks.txt; then
		echo Success
	fi
done

echo "Done checking."
