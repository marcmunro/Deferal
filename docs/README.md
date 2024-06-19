# Deferal - Versatile Non blocking Delays and Deferred Execution

This library provides non-blocking objects for implementing delays.
Multiple delays may run concurrently, and they may be interleaved with
each other.  They also allow a callback function to be defined so that
asynchronous actions may be performed when delays expire.

## Usage

    #include <Deferal.h>

You can use `Deferal` objects in three distinct ways:

### Simple Non-Blocking Delay

    delay = new Deferal(100);
    while (delay.running()) {
        // do some stuff while we wait
     }
     // do stuff at end of delay

This allows us to perform actions while we wait for our delay to
expire.

### Interleaved non-blocking delays

    delay1 = new Deferal(100);
    delay2 = new Deferal(207);
    while (true) {
        result = checkDeferals();
        if (result) {
            if (result == delay1) {
                // do something
            }
            if (result == delay2) {
                // do something else
            }
            result.again(); // Repeat the delay
        }
    }

The `checkDeferals()` call returns `NULL` if all delays are ongoing,
and returns the `Deferal` object for any delay that has completed.   It
does this once only for each completed delay, so if multiple delays
expire at the same time, it will return each of them on subsequent
calls.

Note the use of the `again()` member function.  This restarts the
delay from the expiry of the previous delay period.  This means that
`delay1` will expire at exactly 100 millisecond intervals from its
time of creation, regardless of how much time it takes to process
statements within the loop.

### Asynchronous Actions on Delay Completion

    delay = new Deferal(100, &my_do_func, &param_for_my_do_func);
    while (true) {
        // do your stuff
        checkDeferals();  // This will run my_do_func() when delay is done.
    }

This causes `my_do_func()` to be called with `param_for_my_do_func` as a
parameter, when the delay period expires.

A typical usage of this would be to turn off a LED after (say) 100
milliseconds, while allowing the `arduino` to do something useful in
the meantime.

## Ensuring Deferals Run and Expire

Deferals can only expire if you periodically call one of the functions
that checks them.  For a single Deferal, you can call
Deferal::running() or Deferal::stopped().  If you 
have multiple Deferals you should use Deferal::checkDeferals().  Your Deferals
will not expire unless one of these functions is called.

You must therefore be very careful if you use any blocking I/O
operations.

## Timer Functions

When you create a Deferal you may specify a timer function.  By
default this is the standard millis() function.

If you need greater precision you could use the micros() function, or
you can use your own function.

Note that this function does not have to be based on time, it could
return the number of times a loop has been executed, or the number of
characters read from a serial interface.

## Installation

From gitghub.
