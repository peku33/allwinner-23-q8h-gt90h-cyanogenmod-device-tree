#!/bin/bash

# Author: peku33 <peku33@gmail.com>
# Description: This script will generate PRODUCT_COPY_FILES rules basing on _prebuilt directory. This will NOT fetch or modify source directory content - before running this script it should contain valid system overlay

BASEDIR=device/aliexpress2/polaris_p1
DIR=$BASEDIR/_prebuilt/

echo -n "PRODUCT_COPY_FILES += "
FILES=`find $DIR -type f`
for FILE in ${FILES[*]}
do
	echo -n "$FILE:${FILE#$DIR} "
done