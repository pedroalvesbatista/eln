// HtmlParser.h

#ifndef HTMLPARSER_H

#define HTMLPARSER_H

#include "MarkupData.h"

class HtmlParser {
public:
  HtmlParser(QString html, bool nonewlines=false);
  ~HtmlParser();

  /* HtmlParser attempts to parse a bit of html, extracting tags such as
     <b> and <sup> to build MarkupData. The result is intended to be
     pasted into a TextData.
     Parsing is somewhat simplistic, and is not robust against such nastiness
     as   <div style="badchoice> etcetera">   (which ought to be encoded as
     <div style="badchoice&gt; etcetera">   but isn't necessarily).
     It is therefore recommended that the resulting text is checked against
     a plain text version of the html, if available.
     If nonewlines is given, <p> and <br> tags are removed or replaced with
     spaces.
  */
  QList<MarkupData *> const &markups() { return marks; }
  /* The MarkupData are all owned by the HtmlParser and will be destroyed
     when the parser is. */
  QString text() const { return txt; }
private:
  QList<MarkupData *> marks;
  QString txt;
};

#endif