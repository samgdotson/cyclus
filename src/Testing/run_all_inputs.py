#!/usr/bin/python

import sys
import subprocess
import os
import re
 
def main():
    check_inputs()
    input_path = get_input_path()
    cyclus_path = get_cyclus_path()
    files = get_files(input_path)
    sum = Summary()
    for file in files :
        file_to_test = TestFile(cyclus_path, file) 
        file_to_test.run_tests()
        sum.add_to_summary(file_to_test)
    sum.print_summary()

def check_inputs():
    if len(sys.argv) != 3: 
        print 'Usage: run_all_inputs.py [path_to_cyclus_executable] [path_to_Input_folder]' 
        sys.exit(1) 
 
def get_cyclus_path():
    path = sys.argv[1]
    return path

def get_input_path():
    path = sys.argv[2]
    return path

def get_files(path):
    full_paths=[]
    for root, dirs, files in os.walk(path, followlinks=True):
        if '.git' in dirs:
            dirs.remove('.git')
        for name in files: 
            if re.search("\.xml",name):
                full_paths.append(os.path.join(root, name))
            else :
                files.remove(name)
    print "The files to be tested are:"
    print full_paths
    return full_paths

class Summary():
    """An object to hold the results of all the tests"""
    def __init__(self):
        self.passed = []
        self.failed = []

    def add_to_summary(self, test_file) :
        if test_file.passed : 
            self.passed.append( test_file.infile )
        else :
            self.failed.append( test_file.infile )

    def print_summary(self) :
        print "Tests passed = " + str(len(self.passed))
        print "Tests failed = " + str(len(self.failed))
        print "Failed tests : " 
        for test in self.failed : 
            print test

class TestFile():
    """An object representing the inputxml file to test"""
    def __init__(self, cyclus_path, file_path):
        self.infile = file_path 
        self.cyclus_path = cyclus_path 
        self.passed=True
  
    def run_tests(self):
        """Runs all of the input file tests"""
        output = self.get_output()
        if self.test_no_errors(output) and self.test_expected(output) : 
            self.passed = True
        else :
            self.passed = False

    def get_output(self):
        """Returns the output from running the FileTest"""
        flags = " -v9"
        try :
            p = subprocess.Popen(self.cyclus_path+" "+ self.infile + flags,
                    shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            io_tuple = p.communicate()
            output = io_tuple[0]
        except subprocess.CalledProcessError, e:
            print(e)
        return output
        
    def test_no_errors(self, output):
        """returns true if there were no errors or segfaults running this TestFile"""
        to_ret = True
        print "Test " + self.infile 
        if re.search("ERROR",output) or re.search("Segmentation fault",output):
            to_ret = False
            print " resulted in errors: "
            print output
        else :
            print " passed. "
        return to_ret 

    def test_expected(self, output):
        """This function is currently a placeholder. It is intended to print the 
        difference between the current output and the output gathered the last 
        time the test was run"""
        return True

if __name__ == '__main__' : main()
