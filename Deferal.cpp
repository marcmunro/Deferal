/**
 * @file   Deferal.cpp
 * \code
 *     Author:       Marc Munro
 *     Copyright (c) 2024 Marc Munro
 *     License:      GPL V3
 * 
 * \endcode
 * @brief  
 * Implements the Deferal class.
 * 
 */

#include "Deferal.h"
#include <limits.h>

#ifdef UNIT_TESTING
#define INTEGER int
#else
#define INTEGER static int
#endif

/**
 * @brief Compare unsigned longs, allowing for over/underflow.  
 *
 * This could be achieved more simply by other means, but has the
 * advantage of being explicit.
 */
INTEGER
ulo_cmp(unsigned long x, unsigned long y)
{
    unsigned long diff = x - y;
    if (diff) {
	if (diff > (ULONG_MAX >> 1)) {
	    return -1;
	}
	return 1;
    }
    return 0;
}

/**
 * @var Deferal::deferal_list_
 * @brief The head of a list of currently running Deferal objects.  
 *
 * This is scanned by the checkDeferred() function.  The next item in
 * the list is given by the \link Deferal::next_ next_ \endlink member
 * of the Deferal object.
 */
Deferal *Deferal::deferal_list_ = NULL;


/**
 * @brief Create a new, possibly running, Deferal object.
 *
 * Note that the Deferal for each newly started or restarted delay
 * gets added to our #deferal_list_ list.
 *
 * @param delay  The delay for our deferred operation, based on the
 * units of timer_fn().  This will be the number of milliseconds from
 * now.
 * @param autorepeat  Whether the deferal automatically restarts after
 * it expires.
 * @param start  Whether to start the delay immediately.
 * @param timer_fn  The function to be called to get the current time,
 * in suitable units.  This defaults to millis()
 */
Deferal::Deferal(unsigned long delay, bool autorepeat,
		 bool start, TimerFn timer_fn)
{
    init(delay, autorepeat, start, timer_fn);
}

/**
 * @brief Create a new, possibly running, Deferal object, with a
 * function to be called asynchronously when the delay has expired.
 *
 * Note that the Deferal for each newly started or restarted delay
 * gets added to our #deferal_list_ list.
 *
 * @param delay  The delay for our deferred operation, based on the
 * units of timer_fn().  By default, this will be the number of
 * milliseconds from now.
 * @param fn  The function to be called on completion of our delay.
 * @param param  A parameter to be passed to the above function on
 * completion of our delay.
 * @param autorepeat  Whether the deferal automatically restarts after
 * it expires.
 * @param start  Whether the deferal is to be automatically started.
 * @param timer_fn  The function to be called to get the current time,
 * in suitable units.  This defaults to millis()
 */
Deferal::Deferal(unsigned long delay, PostDeferalFn fn,
		 void *param, bool autorepeat,
		 bool start, TimerFn timer_fn)
{
    init(delay, autorepeat, start, timer_fn);
    defer_fn_ = fn;
    defer_fn_param_ = param;
}

/**
 * @brief Do the donkey-work of setting up a new Deferal for constructors.
 */
void
Deferal::init(unsigned long delay, bool autorepeat,
	      bool start, TimerFn timer_fn)
{
    timer_fn_ = timer_fn;
    delay_time_ = delay;
    remaining_time_ = 0;
    start_time_ = timer_fn();
    defer_fn_ = NULL;
    defer_fn_param_ = NULL;
    next_ = NULL;
    autorepeat_ = autorepeat;
    if (start) {
	start_time_ = timer_fn();
	addDeferalEntry(this);
	status_ = DEFERAL_RUNNING;
    }
    else {
	status_ = DEFERAL_STOPPED;
    }
}

/**
 * @brief Ensure this Deferal is removed from Deferal#deferal_list_ on
 * destruction. 
 */
Deferal::~Deferal()
{
    removeDeferalEntry(this);
}

/**
 * @brief Check whether any deferals have expired.
 * @result An expired Deferal, if one has expired since the last call,
 * else NULL.
 */
Deferal *
Deferal::checkDeferals()
{
    Deferal *entry = deferal_list_;
    while (entry) {
	if (entry->stopped()) {
	    /* The stopped() method will have removed entry from
	     * deferal_list_, so we don't need to. */
	    return entry;
	}
	entry = entry->next_;
    }
    return NULL;
    
}
/**
 * @brief Add a Deferal object to our #deferal_list_.
 * @param entry The new Deferal, to be added to #deferal_list_
 */
void
Deferal::addDeferalEntry(Deferal *entry)
{
    entry->next_ = deferal_list_;
    Deferal::deferal_list_ = entry;
}

/**
 * @brief Remove a Deferal object from our #deferal_list_.
 * @param to_remove The Deferal to be removed from #deferal_list_
 */
void
Deferal::removeDeferalEntry(Deferal *to_remove)
{
    Deferal **p_entry = &deferal_list_;
    while (*p_entry) {
	if (*p_entry == to_remove) {
	    *p_entry = to_remove->next_;
	    return;
	}
	p_entry = &((*p_entry)->next_);
    }
}

/**
 * @brief Start a new delay from now.
 * @param delay Optionally set a new delay period.
 */
void
Deferal::start(unsigned long delay) {
    if (delay) {
	delay_time_ = delay;
    }
    start_time_ = timer_fn_();
    if (status_ != DEFERAL_RUNNING) {
	status_ = DEFERAL_RUNNING;
	addDeferalEntry(this);
    }
}

/**
 * @brief Stop the current delay, possibly running our defer_fn_()
 * @param run_post_fn Whether to run defer_fn_()
 * @param allow_repeat Whether autorepeat should be allowed.
 */
void
Deferal::stop(bool run_post_fn, bool allow_repeat)
{
    if (status_ != DEFERAL_STOPPED) {
	status_ = DEFERAL_STOPPED;
	removeDeferalEntry(this);
	if (run_post_fn && defer_fn_) {
	    defer_fn_(defer_fn_param_);
	}
	if (allow_repeat && autorepeat_) {
	    again();
	}
    }
}

/**
 * @brief Check the current state of a Deferal, expiring it as needed.
 * 
 * If a Deferal has passed its completion time, it will be stopped,
 * possibly running the expiry function, and possibly automatically
 * restarting it if appropriate.
 */
void
Deferal::updateStatus()
{
    if (status_ == DEFERAL_RUNNING) {
	unsigned long now = timer_fn_();
	if ((now - start_time_) >= delay_time_) {
	    stop(true, true);
	}
    }
}

/**
 * @brief Predicate: true if the Deferal is in the stopped state.
 */
bool
Deferal::stopped()
{
    updateStatus();
    return status_ == DEFERAL_STOPPED;
}

/**
 * @brief Predicate: true if the Deferal is in the running state.
 */
bool
Deferal::running()
{
    updateStatus();
    return status_ == DEFERAL_RUNNING;
}

/**
 * @brief Predicate: true if the Deferal is in the paused state.
 */
bool
Deferal::paused()
{
    updateStatus();
    return status_ == DEFERAL_PAUSED;
}

/**
 * @brief Return the status of the Deferal (running, paused, stopped).
 */
deferal_status_t
Deferal::status()
{
    updateStatus();
    return status_;
}

/**
 * @brief Pause a running deferal.
 */
void
Deferal::pause()
{
    updateStatus();
    if (status_ == DEFERAL_RUNNING) {
	unsigned long now = timer_fn_();
	status_ = DEFERAL_PAUSED;
	remaining_time_ = now - start_time_;
    }
}

/**
 * @brief Resume a paused deferal.
 */
void
Deferal::resume()
{
    if (status_ == DEFERAL_PAUSED) {
	unsigned long now = timer_fn_();
	start_time_ = now - remaining_time_;
	status_ = DEFERAL_RUNNING;
    }
}

/**
 * @brief Repeat the last delay from the time of its completion.
 *
 * If the added delay still leaves us stopped, we may run any
 * associated post Deferal function.  This only makes sense for
 * Deferals that have stopped.
 */
void
Deferal::again(unsigned long delay, bool run_post_fn)
{
    if (status_ == DEFERAL_STOPPED) {
	unsigned long now = timer_fn_();
	unsigned long this_delay = delay? delay: delay_time_;
    
	// Set start_time_ to the time it would have automatically
	// restarted, had it done so.
	start_time_ += delay_time_;
	delay_time_ = this_delay;
	while ((start_time_ + delay_time_) < now) {
	    // Running again still leaves the finish time in the past
	    if (run_post_fn && defer_fn_) {
		defer_fn_(defer_fn_param_);
	    }
	    if (!autorepeat_) {
		// If we are to autorepeat, we'll keep running the
		// loop until we caught up and then start ourselves
		// running again.  If not, we are done here.
		return;
	    }
	    start_time_ += delay_time_;
	}
	status_ = DEFERAL_RUNNING;
	addDeferalEntry(this);
    }
}

/**
 * @brief Return the outstanding delay amount at the current time.
 * Note that this may be negative if the delay has expired and not
 * restarted. 
 */
long
Deferal::remaining()
{
    unsigned long now = timer_fn_();
    return delay_time_ - (now - start_time_);
}

/**
 * @brief Set the function to be run when the Deferal expires.
 * 
 * @param fn  The function to be called on completion of our delay.
 * @param param  A parameter to be passed to the above function on
 * completion of our delay.
 */
void
Deferal::setDeferalFn(PostDeferalFn fn, void *param)
{
    defer_fn_ = fn;
    defer_fn_param_ = param;
}

/**
 * @brief Return the delay period for this Deferal.
 */
long
Deferal::delayPeriod()
{
    return delay_time_;
}

/**
 * @brief Set the delay period for this Deferal.
 *
 * @param delay  The delay for our deferred operation, based on the
 * units of Deferal::timer_fn_().  
 */
void
Deferal::setDelay(unsigned long delay)
{
    delay_time_ = delay;
}


#ifdef UNIT_TESTING
/**
 * @brief Reset the deferal list to be empty.
 */
void
Deferal::clearDeferals()
{
    deferal_list_ = NULL;
}

void
Deferal::reset(unsigned long delay, bool autorepeat,
	       bool start, TimerFn timer_fn)
{
    init(delay, autorepeat, start, timer_fn);
}
#endif    

