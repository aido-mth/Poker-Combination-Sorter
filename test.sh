#!/bin/bash
./prepare.sh
./run.sh < ./tests/input.txt > ./tests/tmp.txt
diff ./tests/tmp.txt ./tests/output.txt
rm ./tests/tmp.txt
