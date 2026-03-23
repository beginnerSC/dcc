#!/bin/bash

# Time Zone: should be -0400 in the summer but whatever
TZ_OFFSET="-0500"
COMMIT_TIME="22:00:00"

# Get today's date in YYYY-MM-DD
FINAL_DATE=$(date +%Y-%m-%dT${COMMIT_TIME}${TZ_OFFSET})

# Set git dates
export GIT_AUTHOR_DATE=$FINAL_DATE
export GIT_COMMITTER_DATE=$FINAL_DATE

# Configure git
git config --global user.name "beginnerSC"
git config --global user.email "25188222+beginnerSC@users.noreply.github.com"

# Commit and push
git add *
git commit -m "auto save"
git push