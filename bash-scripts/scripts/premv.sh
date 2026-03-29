#!/bin/bash

# Prefix rename - replaces old prefix with new prefix for all matching files
if [ $# -ne 2 ]; then
    echo "Usage: $0 <old-prefix> <new-prefix>" >&2
    exit 1
fi

for file in *; do
    if [[ "$file" = "$1"* ]]; then
        mv "$file" "$2${file#$1}"
    fi
done