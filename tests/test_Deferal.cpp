
#include "cppunit.h"
#include <Deferal.h>

static unsigned long milli_count = 1000;

unsigned long
millis(void)
{
    return milli_count;
}


static int counter = 0;

    static void
    endDelay(void *ignore)
    {
	counter++;
    }
    

class Cppunit_tests: public Cppunit
{
    /**
     * Run the full set of unit tests for Deferals
     */
    void
    test_list()
    {
	test_single_delay();
	test_autorepeat();
	test_pause();
	test_multiple_delays();
	test_deferal_fn();
    }

    /* Test a single Deferal with simple delays. */
    void
    test_single_delay()
    {
	// TEST: Run 200 unit delay.  Check it is not done until 200
	// units have passed, and that it then stays done.
	milli_count = 1000;
	Deferal delay1(200);
	
	// Not done until milli_count reaches 1200
        CHECKT(!delay1.stopped());
	milli_count = 1100;
        CHECKT(!delay1.stopped());
	milli_count = 1200;
        CHECKT(delay1.stopped());
	milli_count = 1300;
        CHECKT(delay1.stopped());

	// TEST: Restart the delay using again().  Check it is not
	// done until 200 units have passed.
	delay1.again();
        CHECKT(!delay1.stopped());
	milli_count = 1400;
        CHECKT(delay1.stopped());
	milli_count = 1500;
        CHECKT((delay1.status() == DEFERAL_STOPPED));

	// TEST: Restart the delay using again(), and then reset it
	// using start().  Check it is not done until 200 units have
	// passed from start().  Use checkDeferals() to expire the
	// Deferal and test that it returns the expected results.
	delay1.again();
	milli_count = 1550;
        CHECKT(!delay1.stopped());
	delay1.start();
	milli_count = 1749;
	CHECKT(!delay1.stopped());

	//Ensure checkDeferals() returns nothing if there are
	// no newly expired Deferals.
	CHECKP(Deferal::checkDeferals(), NULL);
	milli_count = 1750;
	// Expiry of delay1 Should only be reported once
	CHECKP(Deferal::checkDeferals(), &delay1);  
	CHECKP(Deferal::checkDeferals(), NULL);
        CHECKT(delay1.stopped());
	CHECKP(Deferal::checkDeferals(), NULL);
    }

    /* Test a single Deferal with simple delays. */
    void
    test_autorepeat()
    {
	// TEST: Run 200 unit delay.  Check it is not done until 200
	// units have passed, and that it then stays done.
	milli_count = 1000;
	counter = 0;
	Deferal autodelay(200, endDelay, NULL, true);
	
	milli_count = 1250;
	CHECKP(Deferal::checkDeferals(), NULL);
        CHECKT(counter == 1);
	milli_count = 1450;
	CHECKT(!autodelay.stopped());
	CHECKT(autodelay.running());
        CHECKT(counter == 2);
	milli_count = 2050;
	CHECKT(!autodelay.stopped());
        CHECK(counter, 5);
	CHECKT(autodelay.status() == DEFERAL_RUNNING);
        CHECK(counter, 5);
    }
    
    void
    test_pause()
    {
	// TEST: Check that pause() and resume() do as expected.
	milli_count = 1000;
	Deferal pausedelay(200);
	CHECKT(!pausedelay.stopped());
	CHECKT(!pausedelay.paused());
	CHECKT(pausedelay.running());
	milli_count = 1050;
	pausedelay.pause();
	CHECKT(pausedelay.paused());
	milli_count = 1400;
	CHECKT(pausedelay.paused());
	pausedelay.resume();
	CHECKT(pausedelay.running());
	milli_count = 1549;
	CHECKT(pausedelay.running());
	milli_count = 1550;
	CHECKT(pausedelay.stopped());
	pausedelay.pause();
	CHECKT(pausedelay.stopped());
    }
    
    // Multiple delays, and constructor/destructor tests.
    void
    test_multiple_delays()
    {
	milli_count = 1000;
	Deferal delay1(200);
	Deferal *delay2 = new Deferal(200);
	Deferal delay3(200);
	
	// Delays will be complete at milli_count = 1200
        CHECKT(!delay1.stopped());
	CHECK(delay1.remaining(), 200);
        CHECKT(!delay2->stopped());
        CHECKT(!delay3.stopped());
	milli_count = 1200;
	CHECK(delay1.remaining(), 0);
	CHECKP(Deferal::checkDeferals(), &delay3);  
	CHECKP(Deferal::checkDeferals(), delay2);  
	CHECKP(Deferal::checkDeferals(), &delay1);  
	CHECKP(Deferal::checkDeferals(), NULL);
        CHECKT(delay1.stopped());
        CHECKT(delay2->stopped());
        CHECKT(delay3.stopped());

	// Run all 3 delays again (restarting in different order).
	delay1.again();
	delay3.again();
	delay2->again();
	// Delays will be complete at milli_count = 1400
	CHECKP(Deferal::checkDeferals(), NULL);
	milli_count = 1500;
	CHECKP(Deferal::checkDeferals(), delay2);  
	CHECKP(Deferal::checkDeferals(), &delay3);  
	CHECKP(Deferal::checkDeferals(), &delay1);  
	CHECKP(Deferal::checkDeferals(), NULL);

	// Run 2 delays again.
	delay1.again();
	delay2->again();
	// Delays will be complete at milli_count = 1600
	CHECKP(Deferal::checkDeferals(), NULL);
	milli_count = 1650;
	CHECKP(Deferal::checkDeferals(), delay2);  
	CHECKP(Deferal::checkDeferals(), &delay1);  
	CHECKP(Deferal::checkDeferals(), NULL);

	CHECK(delay3.remaining(), -250);
	delay3.again();
	CHECK(delay3.remaining(), -50);
	delay3.again();
	CHECK(delay3.remaining(), 150);
	CHECKP(Deferal::checkDeferals(), NULL);

	// Now we start them again, and delete delay2
	delay1.again();
	CHECK(delay1.remaining(), 150);
	delay2->again();
	CHECK(delay2->remaining(), 150);
	CHECK(delay3.remaining(), 150);
	// Delays will be complete at milli_count = 1800
	
	delete delay2;
	CHECKP(Deferal::checkDeferals(), NULL);
	milli_count = 1820;
	CHECK(delay3.remaining(), -20);
	CHECK(delay1.remaining(), -20);

	CHECKP(Deferal::checkDeferals(), &delay1);  
	CHECKP(Deferal::checkDeferals(), &delay3);  
	CHECKP(Deferal::checkDeferals(), NULL);

	delay1.again();
	delay3.again();
	{
	    Deferal delay4(200);
	    milli_count = 1999;
	    CHECK(delay1.remaining(), 1);
	    CHECK(delay3.remaining(), 1);
	    CHECK(delay4.remaining(), 21);
	    CHECKP(Deferal::checkDeferals(), NULL);
	    milli_count = 2001;
	    CHECKP(Deferal::checkDeferals(), &delay3);
	    CHECKP(Deferal::checkDeferals(), &delay1);
	    CHECKP(Deferal::checkDeferals(), NULL);
	    milli_count = 2020;
	    CHECKP(Deferal::checkDeferals(), &delay4);
	    // And again, but we will close this block, thereby
	    // deleting delay4
	    delay1.again();
	    delay4.again();
	    delay3.again();
	    // Delays will be complete at milli_count = 2200
	    CHECKP(Deferal::checkDeferals(), NULL);
	}
	milli_count = 2200;
	CHECKP(Deferal::checkDeferals(), &delay3);
	delay1.stop();
	CHECKP(Deferal::checkDeferals(), NULL);
    }    

    void
    test_deferal_fn()
    {
	milli_count = 1000;
	counter = 0;
	Deferal delay(200, endDelay, NULL, true);
	milli_count = 1250;
	CHECKP(Deferal::checkDeferals(), NULL);
        CHECKT(counter == 1);
	delay.setDeferalFn(NULL);
	milli_count = 1450;
	CHECKP(Deferal::checkDeferals(), NULL);
        CHECKT(counter == 1);
	delay.setDeferalFn(endDelay);
	milli_count = 1650;
	CHECKP(Deferal::checkDeferals(), NULL);
        CHECKT(counter == 2);
    }

};


int
main(int argc, char *argv[]) {
    return (new Cppunit_tests)->run();
}

