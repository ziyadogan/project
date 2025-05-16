#!/bin/bash

echo "Starting test suite..."

# Test logları için dizin oluştur
mkdir -p test_logs

# Stress test
echo -e "\nRunning stress test..."
./tests/stress_test > test_logs/stress_test.log 2>&1
if [ $? -eq 0 ]; then
    echo "Stress test passed"
else
    echo "Stress test failed"
    echo "Check test_logs/stress_test.log for details"
fi

# Disconnect test
echo -e "\nRunning disconnect test..."
./tests/disconnect_test > test_logs/disconnect_test.log 2>&1
if [ $? -eq 0 ]; then
    echo "Disconnect test passed"
else
    echo "Disconnect test failed"
    echo "Check test_logs/disconnect_test.log for details"
fi

# Multi survivor test
echo -e "\nRunning multi survivor test..."
./tests/multi_survivor_test > test_logs/multi_survivor_test.log 2>&1
if [ $? -eq 0 ]; then
    echo "Multi survivor test passed"
else
    echo "Multi survivor test failed"
    echo "Check test_logs/multi_survivor_test.log for details"
fi

# Log analizi
echo -e "\nAnalyzing logs..."
echo "Errors found:"
grep -i "error\|fail\|segmentation" test_logs/*.log

echo "Warnings found:"
grep -i "warning" test_logs/*.log

echo -e "\nTest suite completed"
