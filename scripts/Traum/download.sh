#!/bin/sh

rm db.rar

wget -c http://traumlibrary.net/file/db.rar

rm db/*
unrar x db.rar

php cv_traum.php

rm traum.db.zip
zip traum.db.zip myrulib.db
