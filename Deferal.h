/**
 * @file   Deferal.h
 * \code
 *     Author:       Marc Munro
 *     Copyright (c) 2024 Marc Munro
 *     License:      GPL V3
 * 
 * \endcode
 * @brief  
 * Defines the Deferal class.
 * 
 */

#include <Arduino.h>

#ifndef LIB_DEFERAL
#define LIB_DEFERAL

/**
 * @brief Function Prototype for functions called on the expiry of a deferal 
 */
typedef void (*PostDeferalFn)(void *);

/**
 * @brief Function Prototype for timer functions.  
 *
 * The default timer function is millis().
 */
typedef unsigned long (*TimerFn)();

/**
 * @brief The status of a Deferal object.
 *
 * If a Deferal is in the DEFERAL_RUNNING state, it will exist in the
 * linked list of running Deferals, Deferal#deferal_list_.
 */
typedef enum {
    DEFERAL_RUNNING = 42,
    DEFERAL_PAUSED,
    DEFERAL_STOPPED
} deferal_status_t;


#define ONE_SECOND_MS 1000

/**
 * @class Deferal
 * @brief The Deferal class
 * 
 * A Deferal is an object for handling timeouts and other period-based
 * activities.   They provide non-blocking timed operations that can
 * be single-shot or repetitive.  Multiple Deferals can run
 * simultaneously.  A Deferal may be given a function which will be
 * called when it expires.
 *
 * Deferals must be periodically checked by polling for expired
 * Deferals using Deferal::checkDeferals().  This returns the latest
 * unreported expired Deferal.  
 *
 * The basic operations on a Deferal are:
 *  - creation.
 *    The constructors define the delay period, whether to
 *    automatically start, the function to be used to tell the time
 *    (defaulting to millis()) and any function, with parameter, to be
 *    called when the Deferal expires.
 * 
 *  - start 
 *    start() optionally redefines the delay period.  It starts from
 *    the current time.
 * 
 *  - stop
 *    stop() stops the current deferal, optionally running the expiry
 *    function.
 *    
 *  - pause
 *    pause() stops the current deferal, recording the time remaining.
 * 
 *  - resume
 *    resume() resumes the current deferal, for the period given by the
 *    remaining time after a pause.  Resuming a stopped or running
 *    Deferal does nothing.
 * 
 *  - repeat
 *    again() runs the current deferal with the delay period set as if
 *    the Deferal had immediately restarted after completion.  Ie if
 *    the delay period is 1000, but again() was called 100 ticks after
 *    the Deferal completed, the remaining delay period will be 900.
 *    If the Deferal should have run to completion by now, it will
 *    immediately complete and call any post deferal function.
 * 
 *  - test
 *    running(), paused() stopped() and status() give the current
 *    status of a Deferal in different, obvious, ways.
 * 
 *  - modification
 *    setDeferalFn() sets the function to be run on completion of the
 *    Deferal, setDelay() updates the delay time, causing the Deferal
 *    to stop and the post Deferal function to be called if
 *    appropriate.
 *
 */

#ifdef UNIT_TESTING
extern int ulo_cmp(unsigned long x, unsigned long y);
#endif

class Deferal {
  public:
    Deferal(unsigned long delay, bool autorepeat=false,
	    bool start=true, TimerFn timer_fn = millis);
    Deferal(unsigned long delay, PostDeferalFn fn,
	    void *param = NULL,  bool autorepeat=false,
	    bool start=true, TimerFn timer_fn = millis);

    ~Deferal();
    
    static Deferal *checkDeferals();

#ifdef UNIT_TESTING
    static void clearDeferals();
    void reset(unsigned long delay, bool autorepeat,
	       bool start, TimerFn timer_fn);
#endif
    
    void start(unsigned long delay = 0);
    void stop(bool run_post_fn=true, bool allow_repeat=false);
    void pause();
    void resume();
    bool stopped();
    bool paused();
    bool running();
    long remaining();
    long delayPeriod();
    deferal_status_t status();
    void again(unsigned long delay = 0, bool run_post_fn=true);
    void setDeferalFn(PostDeferalFn fn, void *param = NULL);
    void setDelay(unsigned long delay);
  protected:
    static void addDeferalEntry(Deferal *entry);
    static void removeDeferalEntry(Deferal *to_remove);

    static Deferal *deferal_list_;

    void init(unsigned long delay, bool autorepeat,
	      bool start, TimerFn timer_fn);
    void updateStatus();

    /// Whether to automatically restart when we expire 
    bool             autorepeat_; 

    /// The time, in timer_fn_() units, that the Deferal last started to run
    unsigned long    start_time_;

    /// The time, in timer_fn_() units, that the Deferal is to run for
    /// from Deferal#start_time_
    unsigned long    delay_time_;

    /// The time, in timer_fn_() units, that a paused Deferal will
    /// have remaining when it is resumed,
    unsigned long    remaining_time_;

    /// The current status of the Deferal.
    deferal_status_t status_;
    
    /// The function to be called when the Deferal expires.  May be
    /// NULL if nothing is to be done.
    PostDeferalFn defer_fn_;
    
    /// The parameter to be passed to Deferal::defer_fn_()
    void * defer_fn_param_;
    
    /// The function to be called in order to figure out the progress
    /// of a Deferal.  By default this will be millis().
    TimerFn timer_fn_;

    /// For a running Deferal, this identifies the next Deferal in 
    /// Deferal::deferal_list_.  This will be NULL if we are nut
    /// running, or if we are the last Deferal in the list.
    Deferal *next_;   // Allows Deferals to form a linked list.
    
};

#endif
