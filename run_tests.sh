#!/bin/sh
# Builds and runs the original program, the modified program and 4 extra tests,
# then compares each actual output with the hand-predicted output in expected/.
cd "$(dirname "$0")"; mkdir -p actual build; pass=0; fail=0
check() { if diff -q "expected/$1.txt" "actual/$1.txt" >/dev/null; then echo "PASS  $1"; pass=$((pass+1)); else echo "FAIL  $1"; diff "expected/$1.txt" "actual/$1.txt"; fail=$((fail+1)); fi; }
gcc -Wall -Wextra -o build/main stack.c && ./build/main > actual/main.txt; check main
gcc -Wall -Wextra -o build/modified modified.c && ./build/modified > actual/modified.txt; check modified
LINE=$(grep -n '^int main' stack.c | cut -d: -f1)
for t in t1 t2 t3 t4; do
  head -n $((LINE-1)) stack.c > build/$t.c; cat tests/$t.body >> build/$t.c
  gcc -Wall -o build/$t build/$t.c && ./build/$t > actual/$t.txt; check $t
done
echo "Passed: $pass  Failed: $fail"
