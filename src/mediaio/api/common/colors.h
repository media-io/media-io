#ifndef _MEDIAIO_API_COMMON_COLORS_H_
#define _MEDIAIO_API_COMMON_COLORS_H_

#ifdef __cplusplus
extern "C" {
#endif

static const char* kColorNone   = "\E[0m";

static const char* kColorBlack  = "\E[1;30m";
static const char* kColorRed    = "\E[1;31m";
static const char* kColorGreen  = "\E[1;32m";
static const char* kColorYellow = "\E[1;33m";
static const char* kColorPurple = "\E[1;35m";
static const char* kColorCyan   = "\E[1;36m";
static const char* kColorWhite  = "\E[1;37m";

static const char* kColorBlue   = "\E[1m\E[38;5;25m";
static const char* kColorViolet = "\E[1m\E[38;5;135m";
static const char* kColorOrange = "\E[1m\E[38;5;202m";
static const char* kColorPink   = "\E[1m\E[38;5;207m";
static const char* kColorDark   = "\E[1m\E[38;5;217m";

#ifdef __cplusplus
}
#endif

#endif
