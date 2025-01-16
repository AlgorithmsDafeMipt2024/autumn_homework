add_test([=[Test.Simple]=]  /home/iven/Documents/mipt/autumn_homework/task_01/build/task_01_tests [==[--gtest_filter=Test.Simple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Test.Simple]=]  PROPERTIES WORKING_DIRECTORY /home/iven/Documents/mipt/autumn_homework/task_01/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  task_01_tests_TESTS Test.Simple)
