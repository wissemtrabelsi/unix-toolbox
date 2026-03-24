#!/bin/bash
#tests for filetool

PASS=0
FAIL=0
# Get the path to filetool relative to the saved location - works on any machine
FILETOOL="$(dirname "$0")/../filetool"


check() {
	if [ "$1" = "$2" ]; then
		echo "✅ PASS: $3"
		PASS=$((PASS + 1))
	else
		echo "❌ FAIL: $3"
		echo "Expected: $2"
		echo "GOT: $1"
		FAIL=$((FAIL+1))
	fi
}
	
#test 1: copy test

echo "technically its not a bug its an undocumented feature" >/tmp/src.txt
$FILETOOL copy /tmp/src.txt /tmp/dst.txt
result=$(cat /tmp/dst.txt)
check "$result" "technically its not a bug its an undocumented feature" "copy: copies file content"

#test 2: copy, same file rejection

$FILETOOL copy /tmp/src.txt /tmp/src.txt 2>/dev/null
check "$?" "1" "copy: rejects same file"

#test 3: append

echo "I know C" >/tmp/a.txt
echo "I know Git" >/tmp/b.txt
$FILETOOL append /tmp/a.txt /tmp/b.txt
result=$(cat /tmp/b.txt)
#why printf
check "$result" "$(printf 'I know Git\nI know C')" "append: adds file content to the end"

#test 4: reverse

echo "tnedutskreW eht teg ot gniog si messiW" >/tmp/rev.txt

# reverse prints to stdout
result=$($FILETOOL reverse /tmp/rev.txt)
check "$result" "Wissem is going to get the Werkstudent" "reverse: reverses your text"

#test 5: no arguments for ./filetool

$FILETOOL 2>/dev/null
check "$?" "1" "filetool: fails with unknown command"

#test 6:Unknown command fail

$FILETOOL BlaBla 2>/dev/null
check "$?" "1" "filetool: fails with Unknown command"

#cleanup
rm -rf /tmp/src.txt /tmp/dst.txt /tmp/a.txt /tmp/b.txt /tmp/rev.txt

echo ""
echo "Results: ✅PASS:$PASS passed, ❌FAIL: $FAIL failed"
