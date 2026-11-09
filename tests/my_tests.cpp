/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_MyTestSuite_init = false;
#include "/Users/basilfoubert/Documents/CV_Portfolio/Portfolio/ips-prod/tests/my_tests.h"

static MyTestSuite suite_MyTestSuite;

static CxxTest::List Tests_MyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite( "tests/my_tests.h", 8, "MyTestSuite", suite_MyTestSuite, Tests_MyTestSuite );

static class TestDescription_suite_MyTestSuite_testBasisConstructorTest : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_testBasisConstructorTest() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 13, "testBasisConstructorTest" ) {}
 void runTest() { suite_MyTestSuite.testBasisConstructorTest(); }
} testDescription_suite_MyTestSuite_testBasisConstructorTest;

static class TestDescription_suite_MyTestSuite_testBasisMax : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_testBasisMax() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 29, "testBasisMax" ) {}
 void runTest() { suite_MyTestSuite.testBasisMax(); }
} testDescription_suite_MyTestSuite_testBasisMax;

static class TestDescription_suite_MyTestSuite_testMandatoryTest0 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_testMandatoryTest0() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 54, "testMandatoryTest0" ) {}
 void runTest() { suite_MyTestSuite.testMandatoryTest0(); }
} testDescription_suite_MyTestSuite_testMandatoryTest0;

static class TestDescription_suite_MyTestSuite_testMandatoryTest1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_testMandatoryTest1() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 78, "testMandatoryTest1" ) {}
 void runTest() { suite_MyTestSuite.testMandatoryTest1(); }
} testDescription_suite_MyTestSuite_testMandatoryTest1;

static class TestDescription_suite_MyTestSuite_testMandatoryTest2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_testMandatoryTest2() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 104, "testMandatoryTest2" ) {}
 void runTest() { suite_MyTestSuite.testMandatoryTest2(); }
} testDescription_suite_MyTestSuite_testMandatoryTest2;

static class TestDescription_suite_MyTestSuite_testMandatoryTest3 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_MyTestSuite_testMandatoryTest3() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 132, "testMandatoryTest3" ) {}
 void runTest() { suite_MyTestSuite.testMandatoryTest3(); }
} testDescription_suite_MyTestSuite_testMandatoryTest3;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
