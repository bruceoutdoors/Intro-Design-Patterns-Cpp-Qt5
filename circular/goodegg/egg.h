#ifndef EGG_H
#define EGG_H
//start
class Chicken;              /* Forward class declaration. */
class Egg {
 public:
    Chicken* getParent();   /* Okay in declarations if they are pointers. */ 
};
//end
#endif        //  #ifndef EGG_H
