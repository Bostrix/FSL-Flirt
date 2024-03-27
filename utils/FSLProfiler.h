/*! \file FSLProfiler.h
    \brief Contains declaration of class used for profiling

    \author Jesper Andersson
    \version 1.0b, Feb., 2020.
*/
//
// EddyHelperClasses.h
//
// Jesper Andersson, FMRIB Image Analysis Group
//
// Copyright (C) 2020 University of Oxford
//

#ifndef FSLProfiler_h
#define FSLProfiler_h

#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <iomanip>
#include <sys/time.h>

namespace Utilities {

/****************************************************************//**
*
* \brief This is the exception that is being thrown by FSLProfiler
*
********************************************************************/
class FSLProfilerException: public std::exception
{
public:
  FSLProfilerException(const std::string& msg) noexcept : message(std::string("FSLProfiler::") + msg) {}
  ~FSLProfilerException() noexcept {}
  virtual const char * what() const noexcept { return(message.c_str()); }
private:
  std::string message;
};

/****************************************************************//**
*
*  \class FSLProfiler
*
*  \brief Used for profiling
*
*  This class is used to provide profiling information for eddy.
*  It is intended to be very low overhead when profiling is not
*  turned on, so that the "profiling commands" can be left in the
*  code and only incur a performance penalty when profiling is
*  actually turned on.
*
*  The suggested usage is to static declare objects inside individual
*  functions and then start and stop log entries inside that function.
*  Whether profiling actually takes place or not depends on if it has
*  been turned on with a call to the static function SetProfilingOn.
*
*  As an alternative to creating your own FSLProfiler objects, the
*  Default method returns a reference to a singleton instance, which
*  will save all of its output  to "<bfname>.default" (where "<bfname>"
*  is the filename passed to SetProfilingOn).
*
*  The StartEntry and EndEntry methods allow blocks of code to be
*  timed. A time stamp is recorded on calls to StartEntry; on the
*  matching call to EndEntry, the duration is calculated, and a
*  message emitted to the output file.
*
*  \verbatim
main()
{
  FSLProfiler::SetProfilingOn("my_prof_name");

  f1();
}

f1()
{
  static FSLProfiler prof("_"+string(__FILE__)+"_"+string(__func__));
  double key = prof.StartEntry("First bit");
  // Do stuff
  prof.EndEntry(key);
  // "Entry: First bit Duration: 10.0"
  key = prof.StartEntry("Second bit");
  // Do more stuff
  prof.EndEntry(key);
  // "Entry: Second bit Duration: 20.0"
}
*  \endverbatim
*
*
*  The *Accumulate methods allow profiling of sections of code which
*  are executed multiple times. Total number of calls, total execution
*  duration, and average duration per call are recorded.
*
*  \verbatim
main()
{
  FSLProfiler::SetProfilingOn("my_prof_name");

  for (int i = 0; i < 100; i++) {
    f1();
  }
  prof.EndAccumulate();
  // "Entry: First bit Duration 10.0 [ncalls: 100, avg: 0.01]"
  // "Entry: Second bit Duration 20.0 [ncalls: 100, avg: 0.02]"
}

void f1()
{

  static FSLProfiler prof("_"+string(__FILE__)+"_"+string(__func__));

  prof.StartAccumulate("First bit");
  // Do stuff
  prof.StopAccumulate("First bit");
  prof.StartAccumulate("Second bit");
  // Do more stuff
  prof.StopAccumulate("Second bit");
}
*  \endverbatim
*
********************************************************************/

enum class FSLProfilerStatus { Off, On };
class FSLProfiler
{
public:
  FSLProfiler(const std::string& fname);
  ~FSLProfiler();
  FSLProfilerStatus GetStatus() const { return(_status); }

  // Methods to time a block of code
  double StartEntry(const std::string& descrip);
  void   EndEntry(double key);

  // Methods to time repeated execution of a block of code
  void StartAccumulate(const std::string& key);
  void StopAccumulate( const std::string& key);
  void EndAccumulate(  const std::string& key="");

  // Return a default FSLProfiler instance
  static FSLProfiler& Default();

  static void SetProfilingOn(const std::string& bfname);
  static void SetProfilingOff();
  static FSLProfilerStatus GetProfilingStatus() { return(_status); }
  static unsigned int NumberOfProfilers() { return(_profs.size()); }
private:
  static FSLProfilerStatus            _status;   /// Profiling turned off by default;
  static std::string                  _bfname;   /// Total file name is _bfname + _fname
  static std::vector<FSLProfiler*>    _profs;    /// Vector of pointers to all instances of FSLProfiler
  std::string                         _fname;    /// Internal copy of filename
  std::ofstream                       _out;      /// Output streams (files) at muliple "levels"
  std::map<double,std::string>        _ent;      /// Associative array that binds each entry to a time and a descriptive string

  // Entries used by the *Accumulate methods, for timing
  // repeat execution of code blocks. Each entry, accessed
  // by a string key, contains:
  //   - Number of calls (incremented by StartAccumulate)
  //   - Total duration
  //   - Duration of current call (modified by StartAccumulate/EndAccumulate)
  std::map<std::string, std::tuple<int, double, double>> _acc;

  void set_status_on();
  void flush_and_close();
};


} // End namespace Utilities

#endif // End #ifndef FSLProfiler_h
