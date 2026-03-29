#!/bin/bash

# Interactive backup - copies files matching a suffix to ./backup/
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file-extension>" >&2
    exit 1
fi

mkdir -p backup

for file in *; do
    if [[ -f "$file" && "$file" = *"$1" ]]; then
        echo "Do you want to backup '$file'? (yes/no)"
        read answer
        if [ "$answer" = "yes" ]; then
            cp "$file" backup/
            echo "Backed up: $file"
        fi
    fi
done