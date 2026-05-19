#!/bin/bash
read -p "Enter the username to check : " username
while true; do
	if who | grep -q "^$username\b"; then
		echo "Username $username has logged in.."
		break
	else
		echo "User not logged in Checking again in 10s......."
		sleep 10
	fi
done
