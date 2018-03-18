#!/bin/bash

/usr/bin/ctest -R performance_regtest

rm ../src/scripts/performance_regtest_results.py
cat Testing/Temporary/LastTest.log | grep "alloc_regtest =" >> ../src/scripts/performance_regtest_results.py
cat Testing/Temporary/LastTest.log | grep "scan_regtest =" >> ../src/scripts/performance_regtest_results.py

python3 ../src/scripts/plot_performance_regtest.py