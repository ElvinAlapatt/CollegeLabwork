#!/bin/bash
read -p "Enter the file : " filename
if [ ! -f "$filename" ]; then
	echo "file not found!"
	exit 1
fi

hashfile="$filename.hash"

if [ ! -f "$hashfile" ]; then
	sha256sum "$filename" > "$hashfile"
	echo "Hash created And file is being monitored......"
else
	sha256sum -c "$hashfile"
fi
