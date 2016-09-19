// Copyright 2016 The Crashpad Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CRASHPAD_UTIL_MISC_METRICS_H_
#define CRASHPAD_UTIL_MISC_METRICS_H_

#include <inttypes.h>

#include "base/macros.h"
#include "util/file/file_io.h"

namespace crashpad {

//! \brief Container class to hold shared UMA metrics integration points.
//!
//! Each static function in this class will call a `UMA_*` from
//! `base/metrics/histogram_macros.h`. When building Crashpad standalone,
//! (against mini_chromium), these macros do nothing. When built against
//! Chromium's base, they allow integration with its metrics system.
class Metrics {
 public:
  //! \brief Reports the size of a crash report file in bytes. Should be called
  //!     when a new report is written to disk.
  static void CrashReportSize(FileHandle file);

  //! \brief The result of capturing an exception. These are used as metrics
  //!     enumeration values so new values should always be added at the end.
  enum class CaptureResult : int {
    //! \brief The exception capture succeeded normally.
    kSuccess = 0,

    //! \brief Unexpected exception behavior.
    //!
    //! This value is only used on Mac OS X.
    kUnexpectedExceptionBehavior = 1,

    //! \brief Failed due to attempt to suspend self.
    //!
    //! This value is only used on Mac OS X.
    kFailedDueToSuspendSelf = 2,

    //! \brief The process snapshot could not be captured.
    kSnapshotFailed = 3,

    //! \brief The exception could not be initialized.
    kExceptionInitializationFailed = 4,

    //! \brief The attempt to prepare a new crash report in the crash database
    //!     failed.
    kPrepareNewCrashReportFailed = 5,

    //! \brief Writing the minidump to disk failed.
    kMinidumpWriteFailed = 6,

    //! \brief There was a database error in attempt to complete the report.
    kFinishedWritingCrashReportFailed = 7,

    //! \brief The number of values in this enumeration; not a valid value.
    kMaxValue
  };

  //! \brief Reports on the outcome of capturing a report in the exception
  //!     handler.
  static void ExceptionCaptureResult(CaptureResult result);

  //! \brief The exception code for an exception was retrieved.
  //!
  //! These values are OS-specific, and correspond to
  //! MINIDUMP_EXCEPTION::ExceptionCode.
  static void ExceptionCode(uint32_t exception_code);

  //! \brief The exception handler server started capturing an exception.
  static void ExceptionEncountered();

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(Metrics);
};

}  // namespace crashpad

#endif  // CRASHPAD_UTIL_MISC_METRICS_H_
