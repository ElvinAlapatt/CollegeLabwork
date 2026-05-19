#!/bin/bash
read -p "Enter the filename : " filename
if [ -f "$filename" ]; then
	chmod a-x "$filename"
	echo "Execution permission removed..."
else
	echo "File Not Found"
fi
