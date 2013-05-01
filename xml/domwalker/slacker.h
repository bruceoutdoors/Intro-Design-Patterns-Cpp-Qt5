#ifndef SLACKER_H
#define SLACKER_H

#include "domwalker.h"
/**
 
   Slacker.h 
   
   Transforms subset of Slacker's Docbook/XML elements into
   100% pure Docbook/XML.
 
   Most of the slacker tags are borrowed from HTML and are 
   shorthand for other popular docbook tags.
   
   Version 0.01 pre-alpha. Currently only does a small subset of the
   elements.
   
   Author: S. Alan Ezust  ezust at users dot sourceforge dot net
           http://cartan.cas.suffolk.edu/~sae/local
  */

class Slacker : public DomWalker {
public:
    Slacker(QDomDocument doc) : DomWalker(doc) {}

    /**
      Performs some altering of a DOM tree, in place.
    * @param current - the currently visited element in a tree
    * @return current, or another node which should be its replacement.
    */
    virtual QDomElement visit(QDomElement current);
};

#endif        //  #ifndef SLACKER_H

