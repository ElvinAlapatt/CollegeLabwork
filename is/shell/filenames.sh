#!/bin/bash
count=1
for file in ../*;do
	if [ -f "$file" ]; then
		date = $(stat -c %y "$file")
		echo "$count | $file | $date"
		((count++))
	fi
done
