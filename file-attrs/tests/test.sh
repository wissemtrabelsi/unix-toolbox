#!/bin/bash

#Test for lx
PASS=0
FAIL=0
# Get path to lx relative to this script - to work on any machine
LX="$(dirname "$0")/../lx"

check(){
    if [ "$1" = "$2" ]; then # compare actual vs expected
        echo "✅ PASS: $3"
        PASS=$((PASS + 1))
    else
        echo "❌ FAIL:   $3"
        echo " Expected: $2"
        echo " Got:      $1"
        FAIL=$((FAIL + 1))
    fi
}

#test 1 attrib succeeds on valid file
echo "TEST CONTENT" > /tmp/test_file.txt
$LX attrib /tmp/test_file.txt 2>/dev/null 1>/dev/null
check "$?" "0" "attrib:shows file info"
#test 2 -attrib fails with no args
$LX attrib 2>/dev/null
check "$?" "1" "attrib: fails with no args"

#test 3 -ln creates hard link
echo "lx TEST CONTENT" >/tmp/test_ln_file.txt
$LX ln /tmp/test_ln_file.txt /tmp/hard.txt 2>/dev/null
check "$?" "0" "ln: creates Hard link"
#test 4 ln -v hard link,verbose for hardlink
Result=$($LX ln -v /tmp/test_ln_file.txt /tmp/hard2.txt)
check "$Result" "Link /tmp/test_ln_file.txt ==> /tmp/hard2.txt" "ln -v: creates hard link and prints verbose"

#test 5 -ln -s creates symlink
$LX ln -s /tmp/test_ln_file.txt /tmp/sym1.txt
check "$?" "0" "ln -s: creates symbolic link"
#test 6 -ln -sv creates symlink,verbose
Result=$($LX ln -sv /tmp/test_ln_file.txt /tmp/sym2.txt)
check "$Result" "Symlink /tmp/test_ln_file.txt --> /tmp/sym2.txt" "ln -sv: creates hard symlink and prints verbose"

#test 7
$LX 2>/dev/null
check "$?" "1" "lx: fails with no args"
#test 8
$LX blabli 2>/dev/null
check "$?" "1" "lx: fails with unknown args"


#cleanup
rm -f ../lx /tmp/test_file.txt /tmp/test_ln_file.txt /tmp/hard.txt /tmp/hard2.txt /tmp/sym1.txt /tmp/sym2.txt
echo ""
echo "Results: ✅ $PASS passed, ❌ $FAIL failed"