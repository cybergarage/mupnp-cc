#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

#if defined(TENGINE)
#include <tk/tkernel.h>
#endif

#if defined(TENGINE)
#if defined(PROCESS_BASE) /* Process based */
#include <basic.h>
#define MBEG	int main( W ac, TC *av[] )
#define MEND	0
#define DIR	"/SYS/bin/"
#else /* T-Kernel based */
#include <basic.h>
#include <tk/tkernel.h>
#include <sys/pinfo.h>
#define MBEG	ER main( INT ac, UB *av[] )
#define MEND	E_SYS
#define DIR	"/SYS/bin/"
#endif
#endif

#if defined(TENGINE)
MBEG
#else
int main( int argc, char* argv[] )
#endif
{
  // Create the event manager and test controller
  CPPUNIT_NS::TestResult controller;

  // Add a listener that colllects test result
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener( &result );        

  // Add a listener that print dots as test run.
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener( &progress );      

  // Add the top suite to the test runner
  CPPUNIT_NS::TestRunner runner;
  runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, std::cerr );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}
